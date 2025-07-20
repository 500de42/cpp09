#pragma once

#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <sstream>
#include <limits.h>

class PmergeMe
{
    private :
        std::vector<int> A;
        std::list<int> B;
        std::vector<int> m;
        int pair;
        int impair;      
    public :
        int algo(char *av);
        void tri();
        void tri_insert();
        int search();
};
