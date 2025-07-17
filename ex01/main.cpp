#include "RPN.hpp"

int main(int ac, char **av)
{
    if (ac == 1)
    {
        std::cout << "Error: could not open file.\n";
    }
    else if (ac == 2)
    {
        RPN a;
        if (a.parsing(av) == 0)
            a.checkFileBtc(av[1]);
    }
    else
    {
        std::cout << "Error: too files in arguments.\n";
    }
}
