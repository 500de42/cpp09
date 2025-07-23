#pragma once

#include <algorithm>
#include <deque>
#include <iostream>
#include <limits.h>
#include <list>
#include <sstream>
#include <vector>
#include <iomanip>

int	check(std::string a);
int	parsing(std::string a);

class PmergeMe
{
  private:
	std::vector<int> A, B, m, Vector, justForDisplay, Pair;
    std::deque<int> deq;
	int pair, impair;
	clock_t start, startSort, end, endSort;

  public:
	int algo(char **av);
	void tri();
	int triInsert();
	int secondTri();
	int search();
	void display();
	void triSort();
    int findMin();
    int returnPair(int nb);
};
