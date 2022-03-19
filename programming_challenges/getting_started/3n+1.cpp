#include <iostream>
#include <math.h>

int cycle_length(int n)
{
    int res = 1;

    while(n != 1)
    {
        n = (n%2 == 0)? n/2 : (3*n + 1);
        res++;
    }

    return res;
}

int max_cycle_length(int x, int y)
{
    if(x > y) std::swap(x, y);

    int max_cl = 0;
    for(; x <= y; x++)
    {
        max_cl = std::max(max_cl, cycle_length(x));
    }

    return max_cl;
}

int main(int argc, char** argv)
{
    int i, j;

    while (true)
    {
        std::cin >> i >> j;
        
        if(!std::cin) break;
        
        std::cout << i << " " << j << " " << max_cycle_length(i, j) << std::endl;
    }


    return 0;
}