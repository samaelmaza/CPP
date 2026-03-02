#include "DiamondTrap.hpp"

int main(void)
{
	std::cout << "--- DiamondTrap ---" << std::endl;
	DiamondTrap d("Delta");

	std::cout << std::endl;
	d.whoAmI();
	d.attack("target");
	d.guardGate();
	d.highFivesGuys();

	std::cout << std::endl;
	std::cout << "--- Destruction ---" << std::endl;

	return 0;
}
