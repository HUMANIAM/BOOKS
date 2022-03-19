
/*Sample Input
4 4
*...
....
.*..
....
3 5
**...
.....
.*...
0 0
Sample Output
Field #1:
*100
2210
1*10
1110
Field #2:
**100
33200
1*100
*/
#include <iostream>

char mat [100][100] = {};
char adj_mines[100][100] = {};

int n, m;

bool read_mat()
{
    std::cin >> n >> m;
        
    if(n == 0 && m == 0) {return false;};
        
    for(size_t i = 0; i < n; i++) { std::cin >> mat[i];}

    return true;
}

bool has_mine(int i, int j)
{
    if(i < 0 || j < 0) return 0;

    if(i >= n || j >= m) return 0;

    return mat[i][j] == '*';
}

int square_adjacent_mines(int i, int j)
{
    // previous row, previous colum.
    int res = has_mine(i-1, j-1);

    // previous row, same column.
    res += has_mine(i-1, j);

    // previous row, next column.
    res += has_mine(i-1, j+1);

    // same row, previous column.
    res += has_mine(i, j-1);

    // same row, next column.
    res += has_mine(i, j+1);

    // next row, previous column.
    res += has_mine(i+1, j-1);

    // next row, same column.
    res += has_mine(i+1, j);

    // next row, next column.
    res += has_mine(i+1, j+1);

    return res;
}

// for every square compute the adjacent mines for it. then return the whole adjacent mines matrix.
void adjacent_mines()
{
    int res = 0;

    for(size_t i = 0; i < n; i++)
    {
        for(size_t j = 0; j < m; j++)
        {
            if(mat[i][j] == '*')
            {
                adj_mines[i][j] = '*';
            }
            else
            {
                adj_mines[i][j] = 48 + square_adjacent_mines(i, j);
            }
        }
    }
}

void display_adjacent_mines(int k)
{
    std::cout << "Field #" << k << ":\n";

    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < m; j++)
        {
            std::cout << adj_mines[i][j];
        }

        std::cout << "\n";
    }
}

int main(int argc, char** argv)
{
    for(int k = 1; true; k++)
    {
        if(k != 1) std::cout << "\n";

        if(!read_mat()) {break;}

        adjacent_mines();

        display_adjacent_mines(k);
    }

    return 0;
}