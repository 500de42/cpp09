#include "BitcoinExchange.hpp"

int Bitcoin::checkFileCsv()
{
    std::ifstream readFile("data.csv");
    std::string line;
    if (!readFile)
    {
        std::cout << "open error file: \"data.csv\"" << std::endl;
        return 1;
    }
    std::size_t found;
    std::string date;
    std::string val;
    while (getline(readFile, line))
    {
        found = line.find(",");
        if (found != std::string::npos)
        {
            date = line.substr(0, line.length() - found);
            if (date.empty() || csv.count(date))
                break;
            val = line.substr(line[found + 1], line.length());
            if (val.empty())
                break;
            csv.emplace(date, std::stof(val));
        }
    }
}
