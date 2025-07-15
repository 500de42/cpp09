#include "BitcoinExchange.hpp"

int Bitcoin::checkCsv(std::string &line, std::ifstream &readfile)
{
    int point = 0;
    if (line.length() < 12 || line[4] != '-' || line[7] != '-' || line[10] != ',')
    {
        std::cout << "in csv file error date : " << line << std::endl;
        readfile.close();
        return (1);
    }
    {
        std::string a = line.substr(5, 2);
        if (std::atoi(a.c_str()) > 12 ||  std::atoi(a.c_str()) < 1)
        {
            std::cout << "bad input => " << line.substr(0, 11) << std::endl;
            readfile.close();
            return (1);
        }
    }
    { 
        std::string a = line.substr(8, 2);
        if (std::atoi(a.c_str()) > 31 ||  std::atoi(a.c_str()) < 1)
        {
            std::cout << "bad input => " << line.substr(0, 11) << std::endl;
            readfile.close();
            return (1);
        }
    }
    for(size_t i = 0; i < line.length(); i++)
    {
        if (!std::isdigit(line[i]) && i != 4 && i != 7 && i != 10)
        {
            if (line[i] == '.')
            {
                point++;
                if (point > 1)
                    return errorCsv("error format in csv file", readfile);
                else 
                    continue;
            }
            std::cout << "CSV file: only digits characters are accepted to value : " << line << std::endl;
            readfile.close();
            return (1);
        }
    }
    float val = std::atof(&line[11]);
    if (val < 0 || val < -2147483648.0)
        return errorCsv("negative value in csv file", readfile);
    return 0;
}

int Bitcoin::checkVal(std::string &val)
{
    int point = 0;
    if (val.empty())
        return 2;
    else if (val.find(" "))
    {
        size_t it = val.find(" ");
        val = val.substr(0, it);
    }
    std::stringstream ss(val);
    long long a;
    ss >> a;
    if (a < 0)
       return 3;
    else if (a > 1000)
    {
        // std::cout << "valeur" << a << std::endl;
        return 1;
    }
    for(size_t i = 0; i < val.length(); i++)
    {
        if (!std::isdigit(val[i]))
        {
            if (val[i] == '.')
            {
                point++;
            }
            else
                return 4;
        }
    }
    if (point > 1)
        return 4;
    return 0;
}

// int Bitcoin::checkDate(std::string &date)
// {
//     if (date.length() < 10 || date[4] != '-' || date[7] != '-')
//     {
//         std::cout << "error format : " << date << std::endl;
//         exit(1);
//     }
//     else if (date[10] != ',')
//     {
//         std::cout << "error format : " << date << std::endl;
//         exit(1);
//     }
//     for(int i = 0; i < 10; i++)
//     {
//         if (!std::isdigit(date[i]) && i != 4 && i != 7)
//         {
//             std::cout << "only digits characters are accepted : " << date << std::endl;
//             exit(1);
//         }
//     }
//     return 0;
// }

int Bitcoin::errorCsv(const char *line, std::ifstream &readfile)
{
    std::cout << line << std::endl;
    readfile.close();
    return 1;
}

int Bitcoin::checkFileCsv()
{
    std::ifstream readFile("data.csv");
    std::string line;
    std::size_t found = 0;
    std::string date;
    std::string val;
    int i = 0;

    if (!readFile)
        return errorCsv("open error file: \"data.csv\"", readFile);
    else if (readFile.peek() == std::ifstream::traits_type::eof())
    {
        std::cerr << "Le fichier est vide\n";
        return 1;
    }
    while (getline(readFile, line))
    {//line.find("date,exchange_rate") != std::string::npos
        if (line == "date,exchange_rate" && i == 0)
        {
            i++;
            continue;
        }
        else if (i == 0)
            return errorCsv("bad format in csv file", readFile);
        found = line.find(",");
        if (found != std::string::npos)
        {
            date = line.substr(0, found);
            if (csv.count(date))
                return errorCsv("error double detected in csv file", readFile);  
            else if (date.empty())
                return errorCsv("error format in csv file", readFile);
            if (line[found + 1])
                val = line.substr(found + 1);
            else
                return errorCsv("error format in csv file", readFile);
            if (checkCsv(line, readFile))
                return 1;
            std::stringstream a(val);
            float b;
            a >> b;
            csv[date] = b;
        }
        else
            return errorCsv("bad format in csv file", readFile);
    }
    readFile.close();
    return 0;
}

int Bitcoin::checkFileBtc(char *file)
{
    std::ifstream readFile(file);
    std::string line;
    std::size_t found;
    std::string date;
    std::string val;
    int i = 0;

    if (!readFile)
    {
        std::cout << "open error file: " << file << std::endl;
        return(1);
    }
    else if (readFile.peek() == std::ifstream::traits_type::eof())
    {
        std::cerr << "Le fichier est vide\n";
        return 1;
    }
    while (getline(readFile, line))
    {
        if (line == "date | value" && i == 0)
        {
            i++;
            continue;
        }
        else if (i == 0)
        {
            std::cout << "The first line it's not good : " << line << std::endl;
            continue;
        }
        found = line.find("|");
        if (found != std::string::npos)
        {
            if (line[10] != ' ' || line[11] != '|' || line[12] != ' ')
            {
                std::cout << "bad format => " << line << std::endl;
                continue;
            }
            date = line.substr(0, found);
            if (line[found + 1])
                val = line.substr(found + 2);
            else
            {
                std::cout << "bad format => " << line << std::endl;
                continue;
            }
            if (checkVal(val) == 1)
            {
                // std::cout << val << std::endl;
                std::cout << "Error: too large a number.\n";
                continue;
            }
            else if (checkVal(val) == 2)
            {
                std::cout << "Error: bad input => " << line << std::endl;
                continue;
            }
            else if (checkVal(val) == 3)
            {
                std::cout << "Error: not a positive number\n";
                continue; 
            }
            else if (checkVal(val) == 4)
            {
                std::cout << "Error: not valid number\n";
                continue; 
            }
            if (this->csv.count(date))
            {
                std::stringstream ss(val);
                float a;
                ss >> a;
                std::map<std::string, float>::iterator it = csv.lower_bound(date);
                std::cout << date << " => " << val << " = " << (it->second * a) << std::endl;
            }
            else 
            {
                if (csv.empty())
                {
                    std::cout << "The Csv file it's without value" << std::endl;
                    return 1;    
                }
                else
                {
                    std::map<std::string, float>::iterator it = csv.lower_bound(date);
                    if (it != csv.begin() && it->first != date)
                        it--;
                    std::stringstream ss(val);
                    float a;
                    ss >> a;
                    std::cout << date << " => " << val << " = " << it->second * a << std::endl;                    
                }
            }
        }
        else
        {
            std::cout << "Error: bad input => " << line << std::endl;
        }
    }
    readFile.close();
    return 0;
}
