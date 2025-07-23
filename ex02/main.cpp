#include "PmergeMe.hpp"

int PmergeMe::algo2(char **av)
{
    startSort = clock();
	int i = 1;
	while (av[i])
	{
	    std::string a(av[i]);
	    if (check(a) || parsing(a))
	    {
	        std::cout << "Error1 " << check(a) << std::endl;
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
	if (this->m.size() % 2 == 0)
		this->pair = 1;
	else
		this->pair = 0;
	this->tri2();
	if (triInsert2())
	{
		std::cout << "Error2 \n";
		return (1);
	}
	if (secondTri2())
	{
		std::cout << "Error3 \n";
		return (1);
	}
	return (0);
}

void PmergeMe::tri2()
{
	int	a;
	int	b;

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
	int	i;
	int	cle;

	i = 0;
	cle = 0;
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

int PmergeMe::secondTri2()
{
	size_t	j0 = 0, j1;
	int		next;

	if (deq2.empty())
		return (1);
	j0 = 0, j1 = 1;
	while (j1 < deq2.size())
	{
		if (deq2[j1] != -1)
		{
			std::deque<int>::iterator it = std::lower_bound(deq.begin(), deq.end(),
					deq2[j1]);
			deq.insert(it, deq2[j1]);
		}
		deq2[j1] = -1;
		next = j1 + 2 * j0;
		j0 = j1;
		j1 = next;
	}
	deq2.erase(std::remove(deq2.begin(), deq2.end(), -1), deq2.end());
	while (deq2.size())
	{
		std::deque<int>::iterator it = std::lower_bound(deq.begin(), deq.end(),
				deq2.back());
		deq.insert(it, deq2.back());
		deq2.pop_back();
	}
	endSort = clock();
	return (0);
}

int  PmergeMe::findMin2()
{
    int nb = 0;
    std::deque<int>::iterator it = deq2.begin();
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

void PmergeMe::returnPair2()
{
    int mindeq2 = findMin();
    std::deque<int>::iterator it = std::find(deq2.begin(), deq2.end(), mindeq2);
    if (it != deq2.end()) 
    {
        deq2.erase(it);
        A.insert(A.begin(), mindeq2);
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
