#include "Span.hpp"
#include <limits> // for std::numeric_limits

Span::Span() : _maxSize(0) {}

Span::Span(unsigned int N) : _maxSize(N)
{
	_vec.reserve(N);
}

Span::Span(const Span &src) : _maxSize(src._maxSize), _vec(src._vec)
{
}

Span &Span::operator=(const Span &rhs)
{
	if (this != &rhs)
	{
		this->_maxSize = rhs._maxSize;
		this->_vec = rhs._vec;
	}
	return *this;
}

Span::~Span() {}

void Span::addNumber(int n)
{
	if (_vec.size() >= _maxSize)
		throw FullException();
	_vec.push_back(n);
}

int Span::shortestSpan() const
{
	if (_vec.size() < 2)
		throw NotEnoughElementsException();
	std::vector<int> sortedVec = _vec;
	std::sort(sortedVec.begin(), sortedVec.end());
	int shortest = sortedVec[1] - sortedVec[0];
	for (size_t i = 2; i < sortedVec.size(); i++)
	{
		int diff = sortedVec[i] - sortedVec[i - 1];
		if (diff < shortest)
			shortest = diff;
	}
	return shortest;
}

int Span::longestSpan() const
{
	if (_vec.size() < 2)
		throw NotEnoughElementsException();

	int min = *std::min_element(_vec.begin(), _vec.end());
	int max = *std::max_element(_vec.begin(), _vec.end());

	return max - min;
}

