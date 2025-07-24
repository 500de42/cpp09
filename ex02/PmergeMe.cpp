#include "PmergeMe.hpp"

int check(std::string a)
{
    if (a.empty())
        return 1;
    for(std::string::iterator it = a.begin(); it < a.end(); it++)
    {
        if (!std::isdigit(*it) && *it != ' ')
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
        if (token < 0)
            return 1;
        nb_elements++;
    }
    return 0;
}

int  PmergeMe::findMin()
{
    unsigned int nb = 0;
    std::vector<unsigned int>::iterator it = B.begin();
    nb = *it;
    for(it = B.begin(); it != B.end(); it++)
    {
        if (nb > *it)
        {
            nb = *it;
        }
    }
    return nb;
}

int  PmergeMe::findMin2()
{
    unsigned int nb = 0;
    std::deque<unsigned int>::iterator it = deq2.begin();
    nb = *it;
    for(it = deq2.begin(); it != deq2.end(); it++)
    {
        if (nb > *it)
        {
            nb = *it;
        }
    }
    return nb;
}

void PmergeMe::returnPair()
{    affiche(B);
    unsigned int minB = findMin();
    std::vector<unsigned int>::iterator it = std::find(B.begin(), B.end(), minB);
    if (it != B.end()) 
    {
        B.erase(it);
        A.insert(A.begin(), minB);
    }
    affiche(B);
}

unsigned int  PmergeMe::search()
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
        unsigned int a = this->m.back(); this->m.pop_back();
        unsigned int b = this->m.back(); this->m.pop_back();
        if (a > b)
        {
            this->A.push_back(a);
            this->B.push_back(b);
            this->Pair.push_back(std::make_pair(a, b));
        }
        else
        {
            this->A.push_back(b);
            this->B.push_back(a);
            this->Pair.push_back(std::make_pair(b, a));
        }
    }
}

int PmergeMe::triInsert()
{
    int i = 0;
    unsigned int cle = 0;
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
            std::cout << "Error" << std::endl;
            return 1;
        }
        std::istringstream ss(a);
        long token;
        while (ss >> token)
        {
            this->m.push_back(token);
        }
        i++;
    }
	if (hasDuplicate(m))
	{
		std::cout << "Error" << std::endl;
		return (1);
	}
    if (this->m.size() % 2 == 0)
        this->pair = 1;
    else 
        this->pair = 0;
    justForDisplay = m;
    this->tri();
    if (triInsert())
    {
        std::cout << "Error\n";
        return 1;
    }
    if (secondTri())
    {
        std::cout << "Error\n";
        return 1;
    }
    return 0;
}


int PmergeMe::secondTri()
{
    if (B.empty())
        return 1;
    size_t j0 = 0, j1 = 1;
    std::set<unsigned int> insert;

    while(j1 < B.size())
    {    
        if (insert.find(B[j1]) == insert.end())
        {
            std::vector<unsigned int>::iterator it = std::lower_bound(A.begin(), A.end(), B[j1]);
            A.insert(it, B[j1]);
		    insert.insert(B[j1]);
        }
        unsigned int next = j1 + 2 * j0;
        j0 = j1;
        j1 = next;
    }
    while(B.size())
    {
        if (insert.find(B.back()) == insert.end())
		{
            std::vector<unsigned int>::iterator it = std::lower_bound(A.begin(), A.end(), B.back());
            A.insert(it, B.back());
            insert.insert(B.back());
        }
        B.pop_back();
    }
    end = clock();
    return 0;
}

void PmergeMe::display()
{
    if (A.size() > 5)
    {
        std::cout << "Before: "; 
        std::vector<unsigned int>::iterator it = justForDisplay.begin();
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
        std::vector<unsigned int>::iterator it = justForDisplay.begin();
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
    std::cout << std::fixed << std::setprecision(5) << "Time to process a range of " << A.size() << " elements with std::vector : " << tt << " ml\n";
    std::cout << std::fixed << std::setprecision(5) << "Time to process a range of " << deq.size() << " elements with std::deque :  " << t << " ml\n";
}

// [4, 5, 1, 3 ,2]
// [0, 1, 2, 3, 4 ,7]