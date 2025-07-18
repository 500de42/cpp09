#include "PmergeMe.hpp"

int main(int ac, char **av)
{
    if (ac == 1)
    {
        std::cout << "Error: could not open file.\n";
    }
    else if (ac == 2)
    {
        PmergeMe a;
        a.algo(av[1]);
    }
    else
    {
        std::cout << "Error: too files in arguments.\n";
    }
}
