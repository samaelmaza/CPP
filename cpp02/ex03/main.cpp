#include <iostream>
#include "Point.hpp"

int main(void)
{
	// Triangle avec les sommets (0,0), (10,0), (0,10)
	Point a(0.0f, 0.0f);
	Point b(10.0f, 0.0f);
	Point c(0.0f, 10.0f);

	// Tests
	Point inside(2.0f, 2.0f);       // dedans
	Point outside(10.0f, 10.0f);    // dehors
	Point onEdge(5.0f, 0.0f);       // sur un bord → false
	Point onVertex(0.0f, 0.0f);     // sur un sommet → false

	std::cout << "Inside (2,2): " << (bsp(a, b, c, inside) ? "true" : "false") << std::endl;
	std::cout << "Outside (10,10): " << (bsp(a, b, c, outside) ? "true" : "false") << std::endl;
	std::cout << "On edge (5,0): " << (bsp(a, b, c, onEdge) ? "true" : "false") << std::endl;
	std::cout << "On vertex (0,0): " << (bsp(a, b, c, onVertex) ? "true" : "false") << std::endl;

	return 0;
}
