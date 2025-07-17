#pragma once

#include <fstream>
#include <iostream>
#include <stack>
#include <algorithm>
#include <limits.h>
#include <sstream>

int isOPerator(std::string line);

class RPN
{
    private :
        std::stack<int> stack;
    public :
        int parsing(const char **av);

};


