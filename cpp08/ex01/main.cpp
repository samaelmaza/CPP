#include <iostream>
#include <vector>
#include <cstdlib>
#include "Span.hpp"

int main()
{
	std::cout << "=== Subject Test ===" << std::endl;
	try {
		Span sp = Span(5);
		sp.addNumber(6);
		sp.addNumber(3);
		sp.addNumber(17);
		sp.addNumber(9);
		sp.addNumber(11);
		std::cout << "Shortest: " << sp.shortestSpan() << std::endl;
		std::cout << "Longest: " << sp.longestSpan() << std::endl;
	} catch (std::exception &e) {
		std::cerr << e.what() << std::endl;
	}

	std::cout << "\n=== Custom Exceptions Test ===" << std::endl;
	try {
		Span small(1);
		small.addNumber(42);
		std::cout << "Shortest: " << small.shortestSpan() << std::endl; // Should throw
	} catch (std::exception &e) {
		std::cerr << "Caught expected: " << e.what() << std::endl;
	}
	
	try {
		Span small(1);
		small.addNumber(42);
		small.addNumber(43); // Should throw
	} catch (std::exception &e) {
		std::cerr << "Caught expected: " << e.what() << std::endl;
	}

	std::cout << "\n=== 10,000 Numbers Test (Bonus method) ===" << std::endl;
	try {
		Span massive(10000);
		std::vector<int> randomNums(10000);
		
		srand(time(NULL));
		for (int i = 0; i < 10000; i++)
			randomNums[i] = rand();

		// Add all 10000 numbers in one single magical call !
		massive.addNumbers(randomNums.begin(), randomNums.end());
		
		std::cout << "10k Shortest: " << massive.shortestSpan() << std::endl;
		std::cout << "10k Longest: " << massive.longestSpan() << std::endl;
	} catch (std::exception &e) {
		std::cerr << e.what() << std::endl;
	}

	return 0;
}
