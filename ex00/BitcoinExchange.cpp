#include "BitcoinExchange.hpp"

int Bitcoin::checkCsv(std::string &line)
{
    if (line.length() < 12 || line[4] != '-' || line[7] != '-' || line[10] != ',')
    {
        std::cout << "error date : " << line << std::endl;
        exit(1);
    }
    for(size_t i = 0; i < line.length(); i++)
    {
        if (!std::isdigit(line[i]) && i != 4 && i != 7 && i != 9)
        {
            if (line[i] == '.' && i > 10)
            {
                double val = std::atof(&line[11]);
                if (val != 0.0 || val == 0)
                    continue;
            }
            std::cout << "only digits characters are accepted : " << line << std::endl;
            exit(1);
        }
    }
    double val = std::atof(&line[11]);
    if (val < 0 || val > 1000 || val > INT_MAX || val < INT_MIN)
    {
        std::cout << "error value range: " << &line[11] << std::endl;
        exit(1);
    }
    return 0;
}

int Bitcoin::checkVal(std::string &val)
{
    int point = 0;
    if (val.empty())
        return 2;
    if (std::atol(val.c_str()) > 1000)
       return 1;
    else if (std::atol(val.c_str()) < 0)
        return 3;
    for(size_t i = 0; i < val.length(); i++)
    {
        if (!std::isdigit(val[i]))
        {
            if (val[i] == '.')
            {
                point++;
            }
            else
                return 1;
        }
    }
    if (point > 1)
        return 4;
    return 0;
}

int Bitcoin::checkDate(std::string &date)
{
    if (date.length() < 10 || date[4] != '-' || date[7] != '-')
    {
        std::cout << "error format : " << date << std::endl;
        exit(1);
    }
    else if (date[10] != ',')
    {
        std::cout << "error format : " << date << std::endl;
        exit(1);
    }
    for(int i = 0; i < 10; i++)
    {
        if (!std::isdigit(date[i]) && i != 4 && i != 7)
        {
            std::cout << "only digits characters are accepted : " << date << std::endl;
            exit(1);
        }
    }
    return 0;
}

int Bitcoin::checkFileCsv()
{
    std::ifstream readFile("data.csv");
    std::string line;
    if (!readFile)
    {
        std::cout << "open error file: \"data.csv\"" << std::endl;
        exit(1);
    }
    std::size_t found;
    std::string date;
    std::string val;
    int i = 0;
    while (getline(readFile, line))
    {
        if (line == "date,exchange_rate" && i == 0)
        {
            i++;
            continue;
        }
        found = line.find(",");
        if (found != std::string::npos)
        {
            date = line.substr(0, line.length() - found);
            if (date.empty() || csv.count(date))
                continue;
            if (line[found + 1])
                val = line.substr(line[found + 1], line.length());
            if (val.empty())
                continue;
            if (std::atol(val.c_str()) < 0)
            {
                std::cout << "negative value in csv file\n";
                exit(1);
            }
            else if (std::atol(val.c_str()) > 1000)
            {
                std::cout << "too large value in csv file\n";
                continue;
            }   
            std::stringstream a(val);
            float b;
            a >> b;
            csv[date] = b;
        }
        else
        {
            std::cout << "bad format in csv file\n";
        }
    }
    readFile.close();
    return 0;
}

int Bitcoin::checkFileBtc(char *file)
{
    std::ifstream readFile(file);
    std::string line;
    if (!readFile)
    {
        std::cout << "open error file: " << file << std::endl;
        exit(1);
    }
    std::size_t found;
    std::string date;
    std::string val;
    int i = 0;
    while (getline(readFile, line))
    {
        if (line == "date | value" && i == 0)
        {
            i++;
            continue;
        }
        found = line.find("|");
        if (found != std::string::npos)
        {
            if (line[10] != ' ' || line[11] != '|' || line[12] != ' ')
            {
                std::cout << "error format: " << line << std::endl;
                continue;
            }
            date = line.substr(0, line.length() - (found - 1));
            if (line[found + 1])
                val = line.substr(line[found + 1], line.length());
            else
            {
                std::cout << "error format: " << line << std::endl;
                continue;
            }
            if (checkVal(val) == 1)
            {
                std::cout << "error: value too number\n";
                continue;
            }
            else if (checkVal(val) == 2)
            {
                std::cout << "error: bad input => " << date << std::endl;
                continue;
            }
            else if (checkVal(val) == 3)
            {
                std::cout << "error: not a positive number\n";
                continue; 
            }
            else if (checkVal(val) == 4)
            {
                std::cout << "error: not valid number\n";
                continue; 
            }
            if (this->csv.count(date))
            {
                std::stringstream ss(val);
                float a;
                ss >> a;
                std::map<std::string, float>::iterator it = csv.begin();
                std::cout << date << " => " << val << " = " << it->second * a;
            }
        }
        else
        {
            std::cout << "error format: " << line << std::endl;
        }
    }
    readFile.close();
    return 0;
}
