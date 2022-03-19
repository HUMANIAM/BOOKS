
#include <stdio.h>
#include <math.h>
#include <string>
#include <iostream>

const int N = 25;
const int M = 110;
char screen[N][M];
std::string number;
int s, digit_width, digit_height;
int screen_width, screen_height;

struct SquareEdges
{
    bool top, right, bottom, left;

    SquareEdges():top(false), right(false), bottom(false), left(false)
    {}

    SquareEdges(bool t, bool r, bool b, bool l):top(t), right(r), bottom(b), left(l)
    {}
};

void init()
{
    // fill screen with spaces.
    for(int i = 0; i < N; i++)
    {
        for(int j = 0; j < M; j++)
        {
            screen[i][j] = ' ';
        }
    } 

    digit_width = s+2;
    digit_height = 2*s+3; 

    screen_width = (number.size() * digit_width) + (number.size()-1);
    screen_height = digit_height;

}

void write_row(int row_index, int col_index)
{
    // always the first cell in the row is blank.

    int col_start = col_index + 1;
    int col_end = col_index + s;

    for(; col_start <= col_end; col_start++)
    {
        screen[row_index][col_start] = '-';
    }

    // always the last cell in the row is blank.
}

void write_half_column(int start_row_idx, int col_index)
{
    int end_row_idx = start_row_idx + s + 1;

    // always the first cell in the column is blank.

    start_row_idx += 1;

    for(int i = start_row_idx; i < end_row_idx; i++)
    {
        screen[i][col_index] = '|';
    }

    // always the last cell in the column is blank.
}

void write_square(int start_row, int start_col, SquareEdges square_edges)
{
    if(square_edges.top)
    {
        write_row(start_row, start_col);
    }

    if(square_edges.right)
    {
        write_half_column(start_row, (start_col + digit_width - 1));
    }

    if(square_edges.bottom)
    {
        write_row(start_row + s + 1, start_col);
    }

    if(square_edges.left)
    {
        write_half_column(start_row, start_col);
    }

}

void write_digit(int col_start_index, SquareEdges upper_square, SquareEdges lower_square)
{
    write_square(0, col_start_index, upper_square);
    write_square(digit_height/2, col_start_index, lower_square);
}

void write_zero(int col_start_index)
{
    write_digit(col_start_index, {true, true, false, true}, {false, true, true, true});
}

void write_one(int col_start_index)
{
    write_digit(col_start_index, {false, true, false, false}, {false, true, false, false});
}

void write_two(int col_start_index)
{
    write_digit(col_start_index, {true, true, true, false}, {true, false, true, true});
}

void write_three(int col_start_index)
{
    write_digit(col_start_index, {true, true, true, false}, {true, true, true, false});
}

void write_four(int col_start_index)
{
    write_digit(col_start_index, {false, true, true, true}, {true, true, false, false});
}

void write_five(int col_start_index)
{
    write_digit(col_start_index, {true, false, true, true}, {true, true, true, false});
}

void write_six(int col_start_index)
{
    write_digit(col_start_index, {true, false, true, true}, {true, true, true, true});
}

void write_seven(int col_start_index)
{
    write_digit(col_start_index, {true, true, false, false}, {false, true, false, false});
}

void write_eight(int col_start_index)
{
    write_digit(col_start_index, {true, true, true, true}, {true, true, true, true});
}

void write_nine(int col_start_index)
{
    write_digit(col_start_index, {true, true, true, true}, {true, true, true, false});
}


void write_digits()
{
    void (*write_digit[10])(int) = { write_zero, write_one, write_two,
                                     write_three, write_four, write_five,
                                     write_six, write_seven, write_eight, write_nine
                                    };

    for(size_t i = 0; i < number.size(); i++)
    {
        int start_col = i*(digit_width+1);
        int index = number[i] - '0';

        write_digit[index](start_col);
    }   
}

void display_digits()
{
    for(int i = 0; i < screen_height; i++)
    {
        for(int j = 0; j < screen_width; j++)
        {
            std::cout << screen[i][j];
        }

        std::cout << "\n"; 
    } 
}

int main() {
    int test_case = 0;
    while (true)
    {
        std::cin >> s >> number;

        if (s == 0 && number == "0") break;

        // init the display screen.
        init();

        // draw digts.
        write_digits();

        // display digits.
        display_digits();

        std::cout << "\n";
    }
    return 0;
}