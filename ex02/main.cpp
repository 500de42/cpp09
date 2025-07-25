#include "PmergeMe.hpp"

bool hasDuplicate(const std::vector<unsigned int>& vec)
{
    std::set<unsigned int> seen;
    for (size_t i = 0; i < vec.size(); ++i) 
	{
        // insert() renvoie une paire : .second == false si déjà présent
        if (!seen.insert(vec[i]).second)
            return true;  // doublon trouvé
    }
    return false;  // pas de doublon
}

bool hasDuplicate(const std::deque<unsigned int>& vec)
{
    std::set<unsigned int> seen;
    for (size_t i = 0; i < vec.size(); ++i)
	{
        if (!seen.insert(vec[i]).second) 
            return true;
    }
    return false;
}

bool alreadyInsert(std::set<unsigned int>& vec, unsigned int nb)
{
	return vec.find(nb) != vec.end();
}

int PmergeMe::algo2(char **av)
{
    if (!av[1][0] || !av)
    {
        std::cout << "Error\n";
        return 1;
    }
    startSort = clock();
	int i = 1;
	while (av[i])
	{
	    std::string a(av[i]);
	    if (check(a) || parsing(a))
	    {
	        std::cout << "Error"<< std::endl;
	        return (1);
	    }
	    std::istringstream ss(a);
	    long token;
	    while (ss >> token)
	    {
	        this->deqq.push_back(token);
	    }
	    i++;
	}
	if (hasDuplicate(deqq))
	{
		std::cout << "Error" << std::endl;
		return (1);
	}
	if (this->deqq.size() % 2 == 0)
	{
		this->pair = 1;
	}
	else
	{
		this->pair = 0;
	}
	this->tri2();
	if (triInsert2())
	{
		std::cout << "Error\n";
		return (1);
	}
	if (secondTri2())
	{
        if (deq.size() == 1)
        {
			this->endSort = clock();
			return 0;
		}
		std::cout << "Error\n";
		return (1);
	}
	return (0);
}

void PmergeMe::tri2()
{
	int	a;
	int	b;
    if (this->deqq.size() == 1)
    {
        deq.push_back(this->deqq.back()); this->deqq.pop_back();
        return ;
    }
	if (!this->pair)
	{

		this->impair = this->deqq.back();
		this->deqq.pop_back();
		this->deq2.push_back(impair);
		this->pair = 1;
	}
	while (this->deqq.size())
	{
		a = this->deqq.back();
		this->deqq.pop_back();
		b = this->deqq.back();
		this->deqq.pop_back();
		if (a > b)
		{
            this->deq.push_back(a);
			this->deq2.push_back(b);
            this->Pair.push_back(std::make_pair(a, b));
		}
		else
		{
			this->deq.push_back(b);
			this->deq2.push_back(a);
            this->Pair.push_back(std::make_pair(b, a));
		}
	}
}

int PmergeMe::triInsert2()
{
    int i = 0;
    unsigned int cle = 0;

	if (deq.empty())
		return (1);
	for (size_t j = 0; j < deq.size(); ++j)
	{
		cle = deq[j];
		i = j - 1;
		while (i >= 0 && deq[i] > cle)
		{
			deq[i + 1] = deq[i];
			i--;
		}
		deq[i + 1] = cle;
	}
	return (0);
}

void PmergeMe::affiche(std::deque<unsigned int> &a)
{
	for(size_t i = 0; i < a.size(); i++)
	{
		std::cout << a[i] << "\n\n";
	}
}

void PmergeMe::affiche(std::vector<unsigned int> &a)
{
	for(size_t i = 0; i < a.size(); i++)
	{
		std::cout << a[i] << "\n\n";
	}
}

int PmergeMe::secondTri2()
{
	if (deq2.empty())
		return (1);
	size_t	j0 = 0, j1 = 1;
	std::set<unsigned int> insert;
    returnPair2();
	insert.insert(deq.front());
	while (j1 < deq2.size())
	{
        if (insert.find(deq2[j1]) == insert.end())
        {
			std::deque<unsigned int>::iterator it = std::lower_bound(deq.begin(), deq.end(), deq2[j1]);
			deq.insert(it, deq2[j1]);
			insert.insert(deq2[j1]);
		}
        unsigned int next = j1 + 2 * j0;
        j0 = j1;
        j1 = next;
	}
	while (deq2.size())
	{
		if (insert.find(deq2.back()) == insert.end())
		{
			std::deque<unsigned int>::iterator it = std::lower_bound(deq.begin(), deq.end(), deq2.back());
			deq.insert(it, deq2.back());
			insert.insert(deq2.back());
		}
		deq2.pop_back();
	}
	endSort = clock();
	return (0);
}

void PmergeMe::returnPair2()
{
    unsigned int mindeq2 = findMin2();
    std::deque<unsigned int>::iterator it = std::find(deq2.begin(), deq2.end(), mindeq2);
    if (it != deq2.end()) 
    {
    	deq.insert(deq.begin(), mindeq2);
        deq2.erase(it);

    }
}

int	main(int ac, char **av)
{
	PmergeMe a;

	if (ac == 1)
	{
		std::cout << "Error: could not open file.\n";
	}
	else if (ac > 1)
	{
		if (!a.algo(av) && !a.algo2(av))
		{
			a.display();
		}
	}
}
