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
        this->B.push_back(impair);
        this->pair = 1;
    }
    if (this->m.size())
    {
        int a = this->m.back(); this->m.pop_back();
        int b = this->m.back(); this->m.pop_back();
        if (a > b)
        {
            this->A.push_back(a);
            this->B.push_back(b);
        }
        else
        {
            this->A.push_back(b);
            this->B.push_back(a);
        }
        tri();
    }
}

int  PmergeMe::search()
{
    int j;
    int i = 0;
    int cle = 0;
    for(j = 1; A[j - 1] < A[j] && (j) < A.size(); j++)
    {
    }
    return j;
}

void PmergeMe::tri_insert()
{
    int j;
    int i = 0;
    int cle = 0;
    int tmp;
    while(j < A.size())
    {
        j = this->search();
        cle = A[j];
        i = j - 1;
        while (i >= 0 && A[i] > cle)
        {
            A[i + 1] = A[i];
            i--;
            A[i + 1] = cle;
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
    this->tri();
}
