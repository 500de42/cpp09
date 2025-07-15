#include "BitcoinExchange.hpp"

int main(int ac, char **av)
{
    if (ac == 1)
    {
        std::cout << "Error: could not open file.\n";
    }
    else if (ac == 2)
    {
        Bitcoin a;
        if (a.checkFileCsv() == 0)
            a.checkFileBtc(av[1]);
    }
    else
    {
        std::cout << "Error: too files in arguments.\n";
    }
}
