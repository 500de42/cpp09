#include "PmergeMe.hpp"

int check(std::string a)
{
    if (a.empty())
        return 1;
    for(std::string::iterator it = a.begin(); it < a.end(); it++)
    {
        if (*it == '-' && it == a.begin())
            continue;
        else if (!std::isdigit(*it) && *it != ' ')
            return 1;
    }
    return 0;
}

int parsing(std::string a)
{
    std::istringstream ss(a);
    long token;
    int nb_elements = 0;
    while (ss >> token)
    {
        if (token > INT_MAX || token < 0)
            return 1;
        nb_elements++;
    }
    return 0;
}

int  PmergeMe::findMin()
{
    int nb = 0;
    std::vector<int>::iterator it = A.begin();
    nb = *it;
    for(it = A.begin(); it != A.end(); it++)
    {
        if (nb > *it)
        {
            nb = *it;
        }
    }
    return nb;
}

int PmergeMe::returnPair(int nb)
{
    int num = -1;
    for(std::vector<int>::iterator it = Pair.begin(); it != Pair.end(); it++)
    {
        std::cout << *it << "\n\n";
        if (*it == nb)
        {   
            it++;
            num  = *it;
            break;
        }
    }
    for(std::vector<int>::iterator it = B.begin(); it != B.end(); it++)
    {
        if (*it == num)
        {
            B.erase(it);
            return num;
        }
    }
    return -1;
}

int  PmergeMe::search()
{
    size_t j = 1;
    if (A.empty())
        return 0;
    if (A.size() < 2)
        return A.size();
    while (j < A.size() && A[j - 1] < A[j])
        j++;
    return j;
}

void PmergeMe::tri()
{
    if (!this->pair)
    {
        this->impair = this->m.back(); this->m.pop_back();
        this->B.push_back(impair);
        this->pair = 1;
    }
    while (this->m.size())
    {
        int a = this->m.back(); this->m.pop_back();
        int b = this->m.back(); this->m.pop_back();
        if (a > b)
        {
            this->A.push_back(a);
            this->B.push_back(b);
            this->Pair.push_back(a);
            this->Pair.push_back(b);
        }
        else
        {
            this->A.push_back(b);
            this->B.push_back(a);
            this->Pair.push_back(b);
            this->Pair.push_back(a);
        }
    }
}

int PmergeMe::triInsert()
{
    int i = 0;
    int cle = 0;
    if (A.empty())
        return 1;
    for (size_t j = 0; j < A.size(); ++j)
    {
        cle = A[j];
        i = j - 1;
        while (i >= 0 && A[i] > cle)
        {
            A[i + 1] = A[i];
            i--; 
        }
        A[i + 1] = cle;
    }
    return 0;
}

int PmergeMe::algo(char **av)
{    
    start = clock();
    int i = 1;
    while (av[i])
    {
        std::string a(av[i]);
        if (check(a) || parsing(a))
        {
            std::cout << "Error1 " << check(a) << std::endl;
            return 1;
        }
        std::istringstream ss(a);
        long token;
        while (ss >> token)
        {
            this->m.push_back(token);
            this->Vector.push_back(token);
        }
        i++;
    }
    if (this->m.size() % 2 == 0)
        this->pair = 1;
    else 
        this->pair = 0;
    justForDisplay = m;
    this->tri();
    if (triInsert())
    {
        std::cout << "Error2 \n";
        return 1;
    }
    if (secondTri())
    {
        std::cout << "Error3 \n";
        return 1;
    }
    return 0;
}

void PmergeMe::triSort()
{
    startSort = clock();
    std::sort(Vector.begin(), Vector.end());
    endSort = clock();
}

int PmergeMe::secondTri()
{
    if (B.empty())
        return 1;
    size_t j0 = 0, j1 = 1;
    while(j1 < B.size())
    {
        if (B[j1] != -1)
        {
            std::vector<int>::iterator it = std::lower_bound(A.begin(), A.end(), B[j1]);
            A.insert(it, B[j1]);
        }
        B[j1] = -1;
        int next = j1 + 2 * j0;
        j0 = j1;
        j1 = next;
    }
    B.erase(std::remove(B.begin(), B.end(), -1), B.end());
    while(B.size())
    {
        std::vector<int>::iterator it = std::lower_bound(A.begin(), A.end(), B.back());
        A.insert(it, B.back()); B.pop_back();
    }
    end = clock();
    return 0;
}

void PmergeMe::display()
{
    if (A.size() > 5)
    {
        std::cout << "Before: "; 
        std::vector<int>::iterator it = justForDisplay.begin();
        std::cout << *it << " "; it++;
        std::cout << *it << " "; it++;
        std::cout << *it << " "; it++;
        std::cout << *it << " "; it++;
        std::cout << *it << " [...]\n";
        std::cout << "After: "; 
        it = A.begin();
        std::cout << *it << " "; it++;
        std::cout << *it << " "; it++;
        std::cout << *it << " "; it++;
        std::cout << *it << " "; it++;
        std::cout << *it << " [...]\n"; it++;
    }
    else
    {
        std::cout << "Before: "; 
        std::vector<int>::iterator it = justForDisplay.begin();
        for(size_t i = 0; i < justForDisplay.size() - 1; i++)
        {
            std::cout << *it << " "; it++;
        }
        std::cout << *it << " \n"; it++;
        std::cout << "After: "; 
        it = A.begin();
        for(size_t i = 0; i < A.size() - 1; i++)
        {
            std::cout << *it << " "; it++;
        }
        std::cout << *it << " \n";
    }
    double tt = ((end - start) / (double) CLOCKS_PER_SEC * 1000);
    double t = ((endSort - startSort) / (double) CLOCKS_PER_SEC * 1000);
    std::cout << std::fixed << std::setprecision(5) << "Time to process a range of " << A.size() << " elements with std::vector : " << tt << " us\n";
    std::cout << std::fixed << std::setprecision(5) << "Time to process a range of " << A.size() << " elements with std::deque :  " << t << " us\n";
}

// [4, 5, 1, 3 ,2]
// [0, 1, 2, 3, 4 ,7]