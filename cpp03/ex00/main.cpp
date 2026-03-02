#include "ClapTrap.hpp"

int main(void)
{
	ClapTrap a("Alpha");
	ClapTrap b("Bravo");

	a.attack("Bravo");
	b.takeDamage(0);
	b.beRepaired(5);
	a.attack("Bravo");
	b.takeDamage(0);

	return 0;
}
