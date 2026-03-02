#include "ClapTrap.hpp"
#include "ScavTrap.hpp"
#include "FragTrap.hpp"

int main(void)
{
	std::cout << "--- ClapTrap ---" << std::endl;
	ClapTrap a("Alpha");
	a.attack("target");

	std::cout << std::endl;
	std::cout << "--- ScavTrap ---" << std::endl;
	ScavTrap b("Bravo");
	b.attack("target");
	b.guardGate();

	std::cout << std::endl;
	std::cout << "--- FragTrap ---" << std::endl;
	FragTrap c("Charlie");
	c.attack("target");
	c.highFivesGuys();

	std::cout << std::endl;
	std::cout << "--- Destruction ---" << std::endl;

	return 0;
}
