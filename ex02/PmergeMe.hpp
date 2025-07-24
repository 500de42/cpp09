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
#include <set>


int	check(std::string a);
int	parsing(std::string a);
bool hasDuplicate(const std::vector<unsigned int>& vec);
bool hasDuplicate(const std::deque<unsigned int>& vec);
bool alreadyInsert(std::set<unsigned int>& vec, unsigned int nb);
class PmergeMe
{
  private:
	std::vector<unsigned int> A, B, m, justForDisplay;
	std::vector<std::pair<unsigned int, unsigned int> > Pair, Pair2;
    std::deque<unsigned int> deq, deq2, deqq;
	std::set<unsigned int> seen;
	unsigned int pair, impair;
	clock_t start, startSort, end, endSort;

  public:
	int algo(char **av);
	void tri();
	int triInsert();
	int secondTri();
	unsigned int search();
	void display();
    int findMin();
    void returnPair();


	int algo2(char **av);
	void tri2();
	int triInsert2();
	int secondTri2();
    int findMin2();
    void returnPair2();
void affiche(std::vector<unsigned int> &a);
};


