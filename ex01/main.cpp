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
        a.algo(av);
    }
    else
    {
        std::cout << "Error: too files in arguments.\n";
    }
}
