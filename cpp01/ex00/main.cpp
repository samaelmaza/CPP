#include "Zombie.hpp"

int main()
{
	std::cout << "stack test" << std::endl;
	randomChump("Gaston");

	std::cout << "\nheap test" << std::endl;
	Zombie* z = newZombie("Edouard");
	z->announce();

	std::cout << "Edouard is still here" << std::endl;

	delete z;
	std::cout << "Now hes dead" << std::endl;

	return 0;
}
