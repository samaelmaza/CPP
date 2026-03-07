#ifndef WHATEVER_HPP
#define WHATEVER_HPP

// SWAP — swaps the values of two variables
// Hint: use a temporary variable of type T
template <typename T>
void swap(T &a, T &b)
{
	T tmp = a;
	a = b;
	b = tmp;
}

// MIN — returns the smallest of the two values
// If equal, return the second one (b)
template <typename T>
T const &min(T const &a, T const &b)
{
	// TODO
}

// MAX — returns the greatest of the two values
// If equal, return the second one (b)
template <typename T>
T const &max(T const &a, T const &b)
{
	// TODO
}

#endif
