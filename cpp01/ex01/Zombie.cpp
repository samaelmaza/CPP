#include "Zombie.hpp"

void Zombie::announce() const
{
	std::cout << this->_name << ": BraiiiiiiinnnzzzZ..." << std::endl;
}

Zombie::Zombie()
{

}

Zombie::~Zombie()
{
	std::cout << this->_name << " is dead" << std::endl;
}

void Zombie::setName(std::string name)
{
	this->_name = name;
}
