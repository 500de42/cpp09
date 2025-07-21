#pragma once

#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <sstream>
#include <limits.h>
#include <deque>

int check(std::string a);
int parsing(std::string a);

class PmergeMe
{
    private :
        std::vector<int> A;
        std::vector<int> B;
        std::vector<int> m;
        std::deque<int> Test;
        std::vector<int> justForDisplay;
        int pair, impair;
        clock_t start, startSort, end, endSort;
    public :
        int algo(char **av);
        void tri();
        int triInsert();
        int secondTri();
        int search();
        void display();
        void triSort();
};
