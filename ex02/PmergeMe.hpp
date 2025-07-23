#pragma once

#include <algorithm>
#include <deque>
#include <iostream>
#include <limits.h>
#include <list>
#include <sstream>
#include <vector>
#include <iomanip>
#include <utility>

int	check(std::string a);
int	parsing(std::string a);

class PmergeMe
{
  private:
	std::vector<int> A, B, m, justForDisplay;
	std::vector<std::pair<int, int> > Pair, Pair2;
    std::deque<int> deq, deq2, deqq;
	int pair, impair;
	clock_t start, startSort, end, endSort;

  public:
	int algo(char **av);
	void tri();
	int triInsert();
	int secondTri();
	int search();
	void display();
    int findMin();
    void returnPair();


	int algo2(char **av);
	void tri2();
	int triInsert2();
	int secondTri2();
    int findMin2();
    void returnPair2();
};
