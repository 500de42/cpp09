#include "PmergeMe.hpp"

int main(int ac, char **av)
{
    if (ac == 1)
    {
        std::cout << "Error: could not open file.\n";
    }
    else if (ac > 1)
    {
        PmergeMe a;
        if (!a.algo(av))
        {
            a.triSort();
            a.display();
        }
    }
}
