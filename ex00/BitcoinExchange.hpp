#pragma once

#include <fstream>
#include <iostream>
#include <map>
#include <algorithm>
#include <limits.h>
#include <sstream>


class Bitcoin
{
    private :
        std::map<std::string, float> csv;
        std::map<std::string, float> txt;
    public :
        int checkFileCsv();
        int checkFileBtc(char *file);
        int checkDate(std::string &date);
        int checkCsv(std::string &line);
        int checkValCsv(int &val);
        int checkVal(std::string &val);
};
