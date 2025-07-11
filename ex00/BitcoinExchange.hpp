#pragma once

#include <fstream>
#include <iostream>
#include <map>
#include <algorithm>

class Bitcoin
{
    private :
        std::map<std::string, float> csv;
        std::map<std::string, float> txt;
    public :
        int checkFileCsv();
};
