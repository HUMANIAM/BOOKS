
#include <stdio.h>
#include <math.h>
#include <regex>
#include <string>
#include <iostream>

const int N = 8;
char board [N][N];

bool read_chess_board()
{
    bool has_pieces = false;
    std::string line;
    int row = 0;

    while(std::getline(std::cin, line))
    {
        if(line.empty()) break;

        for(size_t i = 0; i < line.size(); i++)
        {
            board[row][i] = line[i];
            has_pieces = has_pieces || (line[i] != '.'); 
        }

        row += 1;
    }

    return has_pieces;
}

bool valid_square(int r, int c)
{
    return (r >= 0 && r < N) && (c >= 0 && c < N);
}

// 0 -> yes,  1 -> invalid indexes, 2 -> empty cell, 3 -> other peice.
int has_piece(int r, int c, char p)
{
    if(!valid_square(r, c)) {return 1; }
    else if(board[r][c] == '.') {return 2; }
    else { return (board[r][c] == p)? 0 : 3; }
}

bool does_diagnoals_have(int king_r, int king_c, char p)
{
    // top-left diagnoal.
    for(int r = king_r-1, c = king_c-1; (r >= 0 && c >= 0); r--, c--)
    {
        int res = has_piece(r, c, p);

        if(res == 0) return true;
        else if(res == 1 || res == 3) break;
    }

    // bottom-right diagnoal.
    for(int r = king_r+1, c = king_c+1; (r < N && c < N); r++, c++)
    {
        int res = has_piece(r, c, p);

        if(res == 0) return true;
        else if(res == 1 || res == 3) break;
    }

    // top-right diagnoal.
    for(int r = king_r-1, c = king_c+1; (r >=0 && c < N); r--, c++)
    {
        int res = has_piece(r, c, p);

        if(res == 0) return true;
        else if(res == 1 || res == 3) break;
    }

    // bottom-left diagnoal.
    for(int r = king_r+1, c = king_c-1; (r < N && c >= 0); r++, c--)
    {
        int res = has_piece(r, c, p);

        if(res == 0) return true;
        else if(res == 1 || res == 3) break;
    }

    return false;
}

bool does_vertical_have(int king_r, int king_c, char p)
{
    // down.
    for(int r = king_r+1; r < N; r++)
    {
        int res = has_piece(r, king_c, p);

        if(res == 0) return true;
        else if(res == 1 || res == 3) break;
    }

    // up.
    for(int r = king_r-1; r >= 0; r--)
    {
        int res = has_piece(r, king_c, p);

        if(res == 0) return true;
        else if(res == 1 || res == 3) break;
    }

    return false;
}

bool does_horizontal_have(int king_r, int king_c, char p)
{
    // right.
    for(int c = king_c+1; c < N; c++)
    {
        int res = has_piece(king_r, c, p);

        if(res == 0) return true;
        else if(res == 1 || res == 3) break;
    }

    // left.
    for(int c = king_c-1; c >= 0; c--)
    {
        int res = has_piece(king_r, c, p);

        if(res == 0) return true;
        else if(res == 1 || res == 3) break;
    }

    return false;

}

bool does_L_shapes_have(int king_r, int king_c, char p)
{
    return  has_piece(king_r-2, king_c-1, p)    == 0 || 
            has_piece(king_r-1, king_c-2, p)    == 0 || 
            has_piece(king_r-2, king_c+1, p)    == 0 || 
            has_piece(king_r-1,   king_c+2, p)  == 0 ||  
            has_piece(king_r+2,   king_c-1, p)  == 0 ||  
            has_piece(king_r+1, king_c-2, p)    == 0 ||  
            has_piece(king_r+2, king_c+1, p)    == 0 ||  
            has_piece(king_r+1, king_c+2, p)    == 0;
}

bool does_square_have(int king_r, int king_c, char p)
{
    return  has_piece(king_r-1, king_c-1, p) == 0 || 
            has_piece(king_r-1, king_c, p)   == 0 || 
            has_piece(king_r-1, king_c+1, p) == 0 || 
            has_piece(king_r,   king_c-1, p) == 0 || 
            has_piece(king_r,   king_c+1, p) == 0 || 
            has_piece(king_r+1, king_c-1, p) == 0 || 
            has_piece(king_r+1, king_c, p)   == 0 || 
            has_piece(king_r+1, king_c+1, p) == 0 ;
}

int king_attacked_by_pawn(int king_r, int king_c)
{
    // [Black king]: 
    if(board[king_r][king_c] == 'k')
    {
        return has_piece(king_r + 1, king_c - 1, 'P') == 0 ||  // check left white pawn.
               has_piece(king_r + 1, king_c + 1, 'P') == 0;    // check right white pawn.
    }
    
    // [White king]
    if(board[king_r][king_c] == 'K')
    {
        return has_piece(king_r - 1, king_c - 1, 'p') == 0 || // check left black pawn.
               has_piece(king_r - 1, king_c + 1, 'p') == 0;   // check right black pawn.
    }

    return false;
}

bool king_attacked_by_king(int king_r, int king_c)
{
    char other_king = board[king_r][king_c] == 'k'? 'K' : 'k';

    return does_square_have(king_r, king_c, other_king);
}

bool king_attacked_by_rook(int king_r, int king_c)
{
    char other_rook = board[king_r][king_c] == 'k' ? 'R' : 'r';

    return does_horizontal_have(king_r, king_c, other_rook) ||
           does_vertical_have(king_r, king_c, other_rook);
}

bool king_attacked_by_knight(int king_r, int king_c)
{
    char other_knight = board[king_r][king_c] == 'k' ? 'N' : 'n';

    return does_L_shapes_have(king_r, king_c, other_knight);
}

bool king_attacked_by_bishop(int king_r, int king_c)
{
    char other_bishop = board[king_r][king_c] == 'k' ? 'B' : 'b';

    return does_diagnoals_have(king_r, king_c, other_bishop);
}

bool king_attacked_by_queen(int king_r, int king_c)
{
    char other_queen = board[king_r][king_c] == 'k' ? 'Q' : 'q';

    return does_diagnoals_have(king_r, king_c, other_queen) ||
           does_horizontal_have(king_r, king_c, other_queen) ||
           does_vertical_have(king_r, king_c, other_queen);
}

void find_king_position(char king, int& row, int& col)
{
    for(int i = 0; i < N; i++)
    {
        for(int j = 0; j < N; j++)
        {
            if(board[i][j] == king)
            {
                row = i, col = j;
                return;
            }
        }
    }
}

bool is_the_king_attacked(char king)
{
    int king_r, king_c;
    find_king_position(king, king_r, king_c);

    // spawn.
    bool attacked = king_attacked_by_pawn(king_r, king_c);
    if(attacked) return true;

    // knight.
    attacked = king_attacked_by_knight(king_r, king_c);
    if(attacked) return true;

    // Bishop.
    attacked = king_attacked_by_bishop(king_r, king_c);
    if(attacked) return true;

    // Rook.
    attacked = king_attacked_by_rook(king_r, king_c);
    if(attacked) return true;

    // Queen.
    attacked = king_attacked_by_queen(king_r, king_c);
    if(attacked) return true;

    // King.
    attacked = king_attacked_by_king(king_r, king_c);
    if(attacked) return true;

    return false;

}

int check_the_check()
{
    // check the black king in check.
    if(is_the_king_attacked('k'))
    {
        return 0;
    }

    // check the white king in check.
    if(is_the_king_attacked('K'))
    {
        return 1;
    }

    return -1;
}

int main(int argc, const char** argv)
{
    int tc = 1;
    while (true)
    {
        // read chess board.
        bool has_pieces = read_chess_board();

        if(!has_pieces) break;

        // if 1 white is in check else if 0 the black one is in check else no checks.
        int res = check_the_check();

        if(res == 1)
        {
            std::cout << "Game #" << tc << ": white king is in check.\n";
        }
        else if(res == 0)
        {
            std::cout << "Game #" << tc << ": black king is in check.\n";
        }
        else
        {
            std::cout << "Game #" << tc << ": no king is in check.\n";
        }

        tc++;
    }
    return 0;
}