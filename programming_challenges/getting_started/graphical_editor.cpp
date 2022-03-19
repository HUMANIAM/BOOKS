
#include <iostream>
#include <string>
#include <map>
#include <set>
#include <algorithm>

char mat [251][251] = {};
bool visited[251][251] = {};

int cols, rows, x, y, x1, x2, y1, y2;
char color;

void swap_if_first_bigger(int& v1, int& v2)
{
    if (v1 > v2)
    {
        std::swap(v1, v2);
    } 
}

void clear_visited_mat()
{
    for(int i = 0; i < rows; i++)
    {
        for(int j = 0; j < cols; j++)
        {
            visited[i][j] = false;
        }
    }
}

void clear_mat()
{
    for(int i = 0; i < rows; i++)
    {
        for(int j = 0; j < cols; j++)
        {
            mat[i][j] = 'O';
        }
    }
}

void creat_mat()
{
    std::cin >> cols >> rows;

    clear_mat();
}

void color_pixel()
{
    std::cin >> x >> y >> color;

    mat[y-1][x-1] = color;
}

void draw_vertical_line()
{
    std::cin >> x >> y1 >> y2 >> color;

    swap_if_first_bigger(y1, y2);

    for(int i = y1 - 1; i < y2; i++)
    {
        mat[i][x-1] = color;
    }
}

void draw_horizontal_line(int y, int x1, int x2, int color)
{
    swap_if_first_bigger(x1, x2);

    for(int j = x1; j <= x2; j++)
    {
        mat[y][j] = color;
    }
}

void draw_horizontal_line()
{
    std::cin >> x1 >> x2 >> y >> color;

    draw_horizontal_line(y-1, x1-1, x2-1, color);
}

void draw_rectangle()
{
    std::cin >> x1 >> y1 >> x2 >> y2 >> color;

    swap_if_first_bigger(y1, y2);

    for(int i = y1 - 1; i < y2; i++)
    {
        draw_horizontal_line(i, x1-1, x2-1, color);
    }
}

void fill_range_color(int x, int y, char new_color, char range_color)
{
    if(x < 0 || x >= cols || y < 0 || y >= rows) return;

    if(visited[y][x] || (mat[y][x] != range_color)) return;

    mat[y][x] = new_color;
    
    visited[y][x] = true;

    // check neighborhoods.
    fill_range_color(x, y-1, new_color, range_color); // top
    fill_range_color(x, y+1, new_color, range_color); // bottom.
    fill_range_color(x-1, y, new_color, range_color); // left.
    fill_range_color(x+1, y, new_color, range_color); // right.
}

void fill_range_color()
{
    clear_visited_mat();

    std::cin >> x >> y >> color;
    
    x--; y--;

    fill_range_color(x, y, color, mat[y][x]);
}

void print_mat()
{
    std::string name;
    
    std::cin >> name;

    std::cout << name << std::endl;

    for(int i = 0; i < rows; i++)
    {
        for(int j = 0; j < cols; j++)
        {
            std::cout << mat[i][j];
        }

        std::cout << std::endl;
    }

}

void execute_command(char command)
{
    const static std::map<char, void(*)()> executers = 
                                        {{'I', creat_mat}, {'C', clear_mat}, {'L', color_pixel},
                                        {'S', print_mat}, {'V', draw_vertical_line}, {'H', draw_horizontal_line}, 
                                        {'K', draw_rectangle}, {'F', fill_range_color}};


    if(executers.find(command) != executers.cend())
    {
        executers.at(command)();
    }
}

int main(int argc, char** argv)
{
    char command;

    while(true)
    {
        std::cin >> command;

        if(command == 'X') break;

        execute_command(command);
    }

    return 0;
}