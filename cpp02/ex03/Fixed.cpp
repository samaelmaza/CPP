#include "Fixed.hpp"


Fixed::Fixed() : _value(0) {}

Fixed::Fixed(const int n) : _value(n << _fractionalBits) {}

Fixed::Fixed(const float n) : _value(roundf(n * (1 << _fractionalBits))) {}

Fixed::Fixed(const Fixed &src) : _value(src._value) {}

Fixed &Fixed::operator=(const Fixed &rhs)
{
	this->_value = rhs.getRawBits();
	return *this;
}

Fixed::~Fixed() {}


int Fixed::getRawBits(void) const
{
	return this->_value;
}

void Fixed::setRawBits(int const raw)
{
	this->_value = raw;
}

float Fixed::toFloat(void) const
{
	return (this->_value / (float)(1 << _fractionalBits));
}

int Fixed::toInt(void) const
{
	return (this->_value >> _fractionalBits);
}

std::ostream &operator<<(std::ostream &out, const Fixed &fixed)
{
	out << fixed.toFloat();
	return out;
}

bool Fixed::operator>(const Fixed &rhs) const
{
	return this->_value > rhs.getRawBits();
}

bool Fixed::operator<(const Fixed &rhs) const
{
	return this->_value < rhs.getRawBits();
}

bool Fixed::operator>=(const Fixed &rhs) const
{
	return this->_value >= rhs.getRawBits();
}

bool Fixed::operator<=(const Fixed &rhs) const
{
	return this->_value <= rhs.getRawBits();
}

bool Fixed::operator==(const Fixed &rhs) const
{
	return this->_value == rhs.getRawBits();
}

bool Fixed::operator!=(const Fixed &rhs) const
{
	return this->_value != rhs.getRawBits();
}

Fixed Fixed::operator+(const Fixed &rhs) const
{
	return Fixed(this->toFloat() + rhs.toFloat());
}

Fixed Fixed::operator-(const Fixed &rhs) const
{
	return Fixed(this->toFloat() - rhs.toFloat());
}

Fixed Fixed::operator*(const Fixed &rhs) const
{
	return Fixed(this->toFloat() * rhs.toFloat());
}

Fixed Fixed::operator/(const Fixed &rhs) const
{
	return Fixed(this->toFloat() / rhs.toFloat());
}

Fixed &Fixed::operator++()
{
	this->_value++;
	return *this;
}

Fixed Fixed::operator++(int)
{
	Fixed tmp(*this);
	this->_value++;
	return tmp;
}

Fixed &Fixed::operator--()
{
	this->_value--;
	return *this;
}

Fixed Fixed::operator--(int)
{
	Fixed tmp(*this);
	this->_value--;
	return tmp;
}

Fixed &Fixed::min(Fixed &a, Fixed &b)
{
	if(a._value < b._value)
		return a;
	else
		return b;
}

const Fixed &Fixed::min(const Fixed &a, const Fixed &b)
{
	if(a._value < b._value)
		return a;
	else
		return b;
}

Fixed &Fixed::max(Fixed &a, Fixed &b)
{
	if(a._value > b._value)
		return a;
	else
		return b;
}

const Fixed &Fixed::max(const Fixed &a, const Fixed &b)
{
	if(a._value > b._value)
		return a;
	else
		return b;
}
