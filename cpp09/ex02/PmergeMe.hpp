#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <iostream>
#include <vector>
#include <deque>
#include <string>
#include <cstdlib>
#include <climits>
#include <algorithm>
#include <ctime>
#include <iomanip>
#include <stdexcept>

class PmergeMe
{
	private:
		std::vector<int> _vec;
		std::deque<int> _deq;

		// Ford-Johnson (merge-insert sort) for each container
		static void _sortVector(std::vector<int> &vec);
		static void _sortDeque(std::deque<int> &deq);

		// Jacobsthal number generator
		static int _jacobsthal(int n);

	public:
		PmergeMe();
		PmergeMe(const PmergeMe &src);
		PmergeMe &operator=(const PmergeMe &rhs);
		~PmergeMe();

		void run(int argc, char **argv);
};

#endif
