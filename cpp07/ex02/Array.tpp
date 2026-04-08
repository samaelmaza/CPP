#ifndef ARRAY_TPP
#define ARRAY_TPP

template <typename T>
Array<T>::Array() : _array(NULL), _size(0)
{
}

template <typename T>
Array<T>::Array(unsigned int n) : _array(new T[n]()), _size(n)
{
}

template <typename T>
Array<T>::Array(const Array &src) : _array(NULL), _size(0)
{
	this->_size = src._size;
	this->_array = new T[src._size];
	for (unsigned int i = 0; i < src._size; i++)
		this->_array[i] = src._array[i];
}

template <typename T>
Array<T> &Array<T>::operator=(const Array &rhs)
{
	if (this != &rhs)
	{
		delete[] this->_array;
		this->_size = rhs._size;
		this->_array = new T[rhs._size];
		for (unsigned int i = 0; i < rhs._size; i++)
			this->_array[i] = rhs._array[i];
	}
	return *this;
}

template <typename T>
Array<T>::~Array()
{
	delete[] this->_array;
}

template <typename T>
T &Array<T>::operator[](unsigned int index)
{
	if (index >= this->_size)
		throw std::exception();
	return this->_array[index];
}

template <typename T>
T const &Array<T>::operator[](unsigned int index) const
{
	if (index >= this->_size)
		throw std::exception();
	return this->_array[index];
}

template <typename T>
unsigned int Array<T>::size() const
{
	return this->_size;
}

#endif
