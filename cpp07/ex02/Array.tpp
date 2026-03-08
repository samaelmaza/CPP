#ifndef ARRAY_TPP
#define ARRAY_TPP

// Default constructor — creates an empty array
template <typename T>
Array<T>::Array() : _array(NULL), _size(0)
{
}

// Constructor with size — creates an array of n elements initialized by default
template <typename T>
Array<T>::Array(unsigned int n) : _array(new T[n]()), _size(n)
{
}

// Copy constructor — deep copy (modifying copy must NOT affect original)
template <typename T>
Array<T>::Array(const Array &src) : _array(NULL), _size(0)
{
	// TODO: allocate new array and copy each element
}

// Assignment operator — deep copy
template <typename T>
Array<T> &Array<T>::operator=(const Array &rhs)
{
	// TODO: delete old array, allocate new one, copy each element
	return *this;
}

// Destructor
template <typename T>
Array<T>::~Array()
{
	// TODO: free the array
}

// operator[] — access element, throw std::exception if out of bounds
template <typename T>
T &Array<T>::operator[](unsigned int index)
{
	// TODO
}

// const version of operator[]
template <typename T>
T const &Array<T>::operator[](unsigned int index) const
{
	// TODO
}

// size — returns the number of elements
template <typename T>
unsigned int Array<T>::size() const
{
	// TODO
}

#endif
