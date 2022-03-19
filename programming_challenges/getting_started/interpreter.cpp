
#include <iostream>
#include <string>

const int N = 1001;
const int M = 10;

int ram[N] = {};
int registers [M] = {};

void init()
{  
    for(int i = 0; i < N; i++) { ram[i] = 0; }
    for(int i = 0; i < M; i++) { registers[i] = 0; }
}

void read_instructions()
{
    std::string line;

    int i = 0;
    while(std::getline(std::cin, line))
    {
        if(line.empty()) break;

        ram[i] = std::stoi(line);

        i += 1;
    }
}

int execute_instructions()
{
    int result = 0, pc = 0;

    while(ram[pc] != 100)
    {
        result += 1;

        int d1 = ram[pc] / 100;
        int d2 = (ram[pc] / 10) % 10;
        int d3 = ram[pc] % 10;

        pc += 1;

       if(d1 == 2)
        {
            registers[d2] = d3;
        }
        else if(d1 == 3)
        {
            registers[d2] = (registers[d2] + d3) % 1000;
        }
        else if(d1 == 4)
        {
            registers[d2] = (registers[d2] * d3) % 1000;
        }
        else if(d1 == 5)
        {
            registers[d2] = registers[d3];
        }
        else if(d1 == 6)
        {
            registers[d2] = (registers[d2] + registers[d3]) % 1000;
        }
        else if(d1 == 7)
        {
            registers[d2] = (registers[d2] * registers[d3]) % 1000;
        }
        else if(d1 == 8)
        {
            registers[d2] = ram[registers[d3]];
        }
        else if(d1 == 9)
        {
            ram[registers[d3]] = registers[d2];
        }
        else
        {
            if(registers[d3] != 0)
            {
                pc = registers[d2];
            }
        }
    };
    
    return result + 1; 
}

int main(int argc, char** argv)
{
    int n;
    std::string line;

    std::cin >> n;
    std::cin.ignore();
    
    // skip the blank line.
    std::getline(std::cin, line);

    for(int i = 0; i < n; i++)
    {
        init();

        read_instructions();

        int r = execute_instructions();

        std::cout << r << std::endl;
        
        if(i < n-1) std::cout << std::endl;
    }

    return 0;
}