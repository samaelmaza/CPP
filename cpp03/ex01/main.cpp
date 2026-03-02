#include "ClapTrap.hpp"
#include "ScavTrap.hpp"

int main(void)
{
	std::cout << "--- Creating ClapTrap ---" << std::endl;
	ClapTrap a("Alpha");
	a.attack("target");

	std::cout << std::endl;
	std::cout << "--- Creating ScavTrap ---" << std::endl;
	ScavTrap b("Bravo");
	b.attack("target");
	b.guardGate();

	std::cout << std::endl;
	std::cout << "--- Destruction ---" << std::endl;

	return 0;
}
