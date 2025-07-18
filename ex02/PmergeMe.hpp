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
        std::list<int> List;
        std::vector<int> Vector;
        std::vector<int> m;
        int pair;
        int impair;      
    public :
        int algo(char *av);
        void tri();
};
