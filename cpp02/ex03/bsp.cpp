#include "Point.hpp"

static Fixed crossProduct(Point const p1, Point const p2, Point const p3)
{
	return (p2.getX() - p1.getX()) * (p3.getY() - p1.getY())
		 - (p2.getY() - p1.getY()) * (p3.getX() - p1.getX());
}

bool bsp(Point const a, Point const b, Point const c, Point const point)
{
	Fixed d1 = crossProduct(a, b, point);
	Fixed d2 = crossProduct(b, c, point);
	Fixed d3 = crossProduct(c, a, point);

	return (d1 > 0 && d2 > 0 && d3 > 0) || (d1 < 0 && d2 < 0 && d3 < 0);
}
