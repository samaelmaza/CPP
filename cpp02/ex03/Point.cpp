#include "Point.hpp"

Point::Point() : _x(0), _y(0) {}

Point::Point(const float x, const float y) : _x(x), _y(y) {}

Point::Point(const Point &src) : _x(src._x), _y(src._y) {}

// operator= ne peut pas vraiment fonctionner car _x et _y sont const
// mais il faut le déclarer pour la forme canonique
Point &Point::operator=(const Point &rhs)
{
	(void)rhs;
	return *this;
}

Point::~Point() {}

Fixed Point::getX(void) const
{
	return this->_x;
}

Fixed Point::getY(void) const
{
	return this->_y;
}
