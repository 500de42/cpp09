#include "PmergeMe.hpp"

int check(std::string a)
{
    for(std::string::iterator it = a.begin(); it < a.end(); it++)
    {
        if (*it == '-' && it == a.begin())
            continue;
        else if (!std::isdigit(*it))
            return 1;
    }
    return 0;
}

int parsing(char *av)
{
    std::string a(av);
    std::istringstream ss(a);
    long token;
    int nb_elements = 0;
    while (ss >> token)
    {
        if (token > INT_MAX || token < INT_MIN)
            return 1;
        nb_elements++;
    }
    return 0;
}

void PmergeMe::tri()
{
    if (!this->pair)
    {
        this->impair = this->m.back(); this->m.pop_back();
        this->pair = 1;
    }
    if (this->m.size())
    {
        int a = this->m.back(); this->m.pop_back();
        int b = this->m.back(); this->m.pop_back();
        if (a > b)
        {
            this->Vector.push_back(a);
            this->List.push_back(b);
        }
        else
        {
            this->Vector.push_back(b);
            this->List.push_back(a);
        }
    }

}

int PmergeMe::algo(char *av)
{    
    std::string a(av);
    if (parsing(av) || check(a))
    {
        std::cout << "Error" << std::endl;
        return 1;
    }
    std::istringstream ss(a);
    long token;
    while (ss >> token)
    { 
        this->m.push_back(token);
    }
    if (this->m.size() % 2 == 0)
        this->pair = 1;
    else 
        this->pair = 0;
    // if (P.size() % 2 == 0)
    // {
    //     while (P.size())
    //     {
    //         nba = P.back(); P.pop_back();
    //         nbb = P.back(); P.pop_back();
    //         if (nba > nbb)
    //         {
    //             Vector.push_back(nba);
    //             List.push_back(nbb);
    //         }
    //         else
    //         {
    //             Vector.push_back(nbb);
    //             List.push_back(nba);
    //         }
    //     }
    // }
    // else
    // {
    //     while (P.size() != 1)
    //     {
    //         nba = P.back(); P.pop_back();
    //         nbb = P.back(); P.pop_back();
    //         if (nba > nbb)
    //         {
    //             Vector.push_back(nba);
    //             List.push_back(nbb);
    //         }
    //         else
    //         {
    //             Vector.push_back(nbb);
    //             List.push_back(nba);
    //         }
    //     }
    //     List.push_back(P.back());
    // }
}
