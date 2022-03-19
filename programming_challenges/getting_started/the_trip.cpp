#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <iomanip> 

int costs[1000];
int n;

int to_cents(const std::string& str)
{
    size_t pos = str.find('.');
    int dollars = std::stoi(str.substr(0, pos));
    int cents = std::stoi(str.substr(pos+1));
    return dollars*100 + cents;
}

int read_total_cents(int n)
{
    int sum = 0;

    for(int i = 0; i < n; i++)
    {
        std::string s;
        std::cin >> s;

        costs[i] = to_cents(s);
        sum += costs[i];
    }

    return sum;
}

int main() 
{
    int n;

    while(true)
    {
        std::cin >> n;
        if(n == 0) break;

        double avg_cents = double(read_total_cents(n))/n;
        double taken = 0, given = 0;

        for(int i = 0; i < n; i++)
        {
            double diff = costs[i] - avg_cents;
            if (diff < 0)
            {
                taken += -((int) diff) / 100.0;
            } 
            else
            {
                given += ((int) diff) / 100.0;
            }
        }

        printf("$%.2f\n", taken > given ? taken : given);
    }           
      
    return 0;
}