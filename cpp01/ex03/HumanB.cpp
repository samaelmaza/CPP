#include "HumanB.hpp"

HumanB::HumanB(std::string name)
{
	this->_name = name;
	this->_weapon = NULL;
}

HumanB::~HumanB()
{

}

void HumanB::attack()
{
	if(_weapon == NULL)
		std::cout << "error: no weapon" << std::endl;
	else
		std::cout << this->_name << " attacks with their " << _weapon->getType() << std::endl;
}

void HumanB::setWeapon(Weapon &weapon)
{
	this->_weapon = &weapon;
}
