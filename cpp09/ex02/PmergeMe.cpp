#include "PmergeMe.hpp"

// ==================== Orthodox Canonical Form ====================

PmergeMe::PmergeMe() {}

PmergeMe::PmergeMe(const PmergeMe &src) : _vec(src._vec), _deq(src._deq) {}

PmergeMe &PmergeMe::operator=(const PmergeMe &rhs)
{
	if (this != &rhs)
	{
		this->_vec = rhs._vec;
		this->_deq = rhs._deq;
	}
	return *this;
}

PmergeMe::~PmergeMe() {}

// ==================== Jacobsthal Number ====================
// Jacobsthal sequence: 0, 1, 1, 3, 5, 11, 21, 43, 85...
// Formula: J(n) = J(n-1) + 2 * J(n-2)
// This dictates the optimal insertion order to minimize comparisons.

int PmergeMe::_jacobsthal(int n)
{
	if (n == 0) return 0;
	if (n == 1) return 1;
	int prev2 = 0;
	int prev1 = 1;
	int curr = 0;
	for (int i = 2; i <= n; i++)
	{
		curr = prev1 + 2 * prev2;
		prev2 = prev1;
		prev1 = curr;
	}
	return curr;
}

// ==================== Ford-Johnson for std::vector ====================

void PmergeMe::_sortVector(std::vector<int> &vec)
{
	// Base case: nothing to sort
	if (vec.size() <= 1)
		return;

	// ===================== STEP 1 : PAIRING =====================
	bool hasStraggler = (vec.size() % 2 != 0);
	int straggler = -1;
	if (hasStraggler)
	{
		straggler = vec.back(); // Extract leftover element
		vec.pop_back();			// Ensure even pairs
	}

	std::vector<std::pair<int, int> > pairs;
	for (size_t i = 0; i < vec.size(); i += 2)
	{
		// Store the larger element as 'first' (winner) and smaller as 'second' (loser)
		if (vec[i] > vec[i + 1])
			pairs.push_back(std::make_pair(vec[i], vec[i + 1]));
		else
			pairs.push_back(std::make_pair(vec[i + 1], vec[i]));
	}

	// ===================== STEP 2 : RECURSION =====================
	std::vector<int> winners;
	for (size_t i = 0; i < pairs.size(); ++i)
		winners.push_back(pairs[i].first); // Extract winners

	_sortVector(winners); // Recursively sort the winners

	// ===================== STEP 3 : FIND LOSERS =====================
	std::vector<int> pend;
	// Iterate through our sorted winners
	for (size_t i = 0; i < winners.size(); ++i)
	{
		// Match each winner to its original loser pair
		for (std::vector<std::pair<int, int> >::iterator it = pairs.begin(); it != pairs.end(); ++it)
		{
			if (it->first == winners[i])
			{
				pend.push_back(it->second); // Add matched loser
				pairs.erase(it);			// Remove pair to safely handle duplicate values
				break;
			}
		}
	}

	// ===================== STEP 4 : MAIN CHAIN =====================
	std::vector<int> mainChain = winners;

	// ===================== STEP 5 : PUSH FIRST PEND =====================
	if (!pend.empty())
	{
		// pend[0] lost to the smallest winner, so it's guaranteed to be the smallest overall
		mainChain.insert(mainChain.begin(), pend[0]);
	}

	// ===================== STEP 6 : INSERT REST VIA JACOBSTHAL =====================
	size_t pendSize = pend.size();
	if (pendSize > 1)
	{
		int k = 3;
		size_t prevJac = 1; // Start index (pend[0] is already inserted)
		size_t currJac = _jacobsthal(k);

		// Process the remaining pend elements
		while (prevJac < pendSize)
		{
			// Bound checking so we don't read past pend limits
			size_t end = std::min(static_cast<size_t>(currJac), pendSize);
			
			// Insert elements in reverse order to minimize the binary search range
			for (size_t i = end; i > prevJac; --i)
			{
				int loserToInsert = pend[i - 1]; // 0-based indexing
				
				// Binary search finds the optimal insertion point
				std::vector<int>::iterator pos = std::lower_bound(mainChain.begin(), mainChain.end(), loserToInsert);
				mainChain.insert(pos, loserToInsert);
			}

			// Move to the next Jacobsthal cycle
			prevJac = currJac;
			k++;
			currJac = _jacobsthal(k);
		}
	}

	// ===================== STEP 7 : STRAGGLER =====================
	if (hasStraggler)
	{
		std::vector<int>::iterator pos = std::lower_bound(mainChain.begin(), mainChain.end(), straggler);
		mainChain.insert(pos, straggler);
	}

	// Final assignment
	vec = mainChain;
}

// ==================== Ford-Johnson for std::deque ====================
// Exact same logic as _sortVector, but taking advantage of push_front for pend[0]

void PmergeMe::_sortDeque(std::deque<int> &deq)
{
	if (deq.size() <= 1)
		return;

	bool hasStraggler = (deq.size() % 2 != 0);
	int straggler = -1;
	if (hasStraggler)
	{
		straggler = deq.back();
		deq.pop_back();
	}

	std::deque<std::pair<int, int> > pairs;
	for (size_t i = 0; i < deq.size(); i += 2)
	{
		if (deq[i] > deq[i + 1])
			pairs.push_back(std::make_pair(deq[i], deq[i + 1]));
		else
			pairs.push_back(std::make_pair(deq[i + 1], deq[i]));
	}

	std::deque<int> winners;
	for (size_t i = 0; i < pairs.size(); ++i)
		winners.push_back(pairs[i].first);

	_sortDeque(winners);

	std::deque<int> pend;
	for (size_t i = 0; i < winners.size(); ++i)
	{
		for (std::deque<std::pair<int, int> >::iterator it = pairs.begin(); it != pairs.end(); ++it)
		{
			if (it->first == winners[i])
			{
				pend.push_back(it->second);
				pairs.erase(it);
				break;
			}
		}
	}

	std::deque<int> mainChain = winners;

	if (!pend.empty())
	{
		mainChain.push_front(pend[0]);
	}

	size_t pendSize = pend.size();
	if (pendSize > 1)
	{
		int k = 3;
		size_t prevJac = 1;
		size_t currJac = _jacobsthal(k);

		while (prevJac < pendSize)
		{
			size_t end = std::min(static_cast<size_t>(currJac), pendSize);
			
			for (size_t i = end; i > prevJac; --i)
			{
				int loserToInsert = pend[i - 1];
				std::deque<int>::iterator pos = std::lower_bound(mainChain.begin(), mainChain.end(), loserToInsert);
				mainChain.insert(pos, loserToInsert);
			}

			prevJac = currJac;
			k++;
			currJac = _jacobsthal(k);
		}
	}

	if (hasStraggler)
	{
		std::deque<int>::iterator pos = std::lower_bound(mainChain.begin(), mainChain.end(), straggler);
		mainChain.insert(pos, straggler);
	}

	deq = mainChain;
}

// ==================== Main entry point ====================

void PmergeMe::run(int argc, char **argv)
{
	// ===================== PARSING =====================
	for (int i = 1; i < argc; ++i)
	{
		std::string arg = argv[i];
		if (arg.empty())
			throw std::runtime_error("Error");
		
		for (size_t j = 0; j < arg.length(); ++j)
		{
			if (j == 0 && arg[j] == '+') continue;
			if (!isdigit(arg[j]))
				throw std::runtime_error("Error");
		}
		
		long num = std::strtol(arg.c_str(), NULL, 10);
		if (num < 0 || num > INT_MAX)
			throw std::runtime_error("Error");
			
		_vec.push_back(static_cast<int>(num));
		_deq.push_back(static_cast<int>(num));
	}

	// ===================== DISPLAY BEFORE =====================
	std::cout << "Before: ";
	for (size_t i = 0; i < _vec.size(); ++i)
	{
		std::cout << _vec[i] << " ";
		// Truncate output for massive lists to avoid console spam
		if (i == 4 && _vec.size() > 5)
		{
			std::cout << "[...]";
			break;
		}
	}
	std::cout << std::endl;

	// ===================== SORT + TIMING =====================
	clock_t startVec = clock();
	_sortVector(_vec);
	clock_t endVec = clock();
	double timeVec = (double)(endVec - startVec) / CLOCKS_PER_SEC * 1000000.0;

	clock_t startDeq = clock();
	_sortDeque(_deq);
	clock_t endDeq = clock();
	double timeDeq = (double)(endDeq - startDeq) / CLOCKS_PER_SEC * 1000000.0;

	// ===================== DISPLAY AFTER =====================
	std::cout << "After:  ";
	for (size_t i = 0; i < _vec.size(); ++i)
	{
		std::cout << _vec[i] << " ";
		if (i == 4 && _vec.size() > 5)
		{
			std::cout << "[...]";
			break;
		}
	}
	std::cout << std::endl;

	// ===================== DISPLAY TIMING =====================
	std::cout << "Time to process a range of " << _vec.size() 
			  << " elements with std::vector : " << std::fixed << std::setprecision(5) << timeVec << " us" << std::endl;
	std::cout << "Time to process a range of " << _deq.size() 
			  << " elements with std::deque  : " << std::fixed << std::setprecision(5) << timeDeq << " us" << std::endl;
}
