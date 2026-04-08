#ifndef SPAN_HPP
#define SPAN_HPP

#include <vector>
#include <stdexcept>
#include <algorithm>
#include <iostream>

class Span
{
	private:
		unsigned int		_maxSize;
		std::vector<int>	_vec;
		Span(); // private default constructor to enforce the size parameter

	public:
		Span(unsigned int N);
		Span(const Span &src);
		Span &operator=(const Span &rhs);
		~Span();

		void	addNumber(int n);
		int		shortestSpan() const;
		int		longestSpan() const;

		// Exceptions
		class FullException : public std::exception {
			public: virtual const char* what() const throw() { return "Span is full"; }
		};
		class NotEnoughElementsException : public std::exception {
			public: virtual const char* what() const throw() { return "Not enough elements to find a span"; }
		};

		// BONUS: Add multiple numbers from a range of iterators
		// Since it's a template, the implementation stays in the header
		template <typename Iterator>
		void addNumbers(Iterator begin, Iterator end)
		{
			for (Iterator it = begin; it != end; it++)
			{
				addNumber(*it);
			}
		}
};

#endif
