#include "ClapTrap.hpp"

ClapTrap::ClapTrap() : _name("default"), _hitPoints(10), _energyPoints(10), _attackDamage(0)
{
	std::cout << "ClapTrap default constructor called" << std::endl;
}

ClapTrap::ClapTrap(std::string name) : _name(name), _hitPoints(10), _energyPoints(10), _attackDamage(0)
{
	std::cout << "ClapTrap " << this->_name << " constructor called" << std::endl;
}

ClapTrap::ClapTrap(const ClapTrap &src)
{
	std::cout << "ClapTrap copy constructor called" << std::endl;
	*this = src;
}

ClapTrap &ClapTrap::operator=(const ClapTrap &rhs)
{
	std::cout << "ClapTrap copy assignment operator called" << std::endl;
	this->_name = rhs._name;
	this->_hitPoints = rhs._hitPoints;
	this->_energyPoints = rhs._energyPoints;
	this->_attackDamage = rhs._attackDamage;
	return *this;
}

ClapTrap::~ClapTrap()
{
	std::cout << "ClapTrap " << this->_name << " destructor called" << std::endl;
}

void ClapTrap::attack(const std::string &target)
{
	if(this->_energyPoints <= 0 || this->_hitPoints <= 0)
		return ;
	this->_energyPoints -= 1;
	std::cout << "ClapTrap " << this->_name << " attacks " << target << " causing " << this->_attackDamage << " points of damage" << std::endl;
}

void ClapTrap::takeDamage(unsigned int amount)
{
	this->_hitPoints -= amount;
	std::cout << "ClapTrap " << this->_name << " received " << amount << " damages" << std::endl;
}

void ClapTrap::beRepaired(unsigned int amount)
{
	if(this->_energyPoints <= 0 || this->_hitPoints <= 0)
		return ;
	this->_energyPoints -= 1;
	this->_hitPoints += amount;
	std::cout << "ClapTrap " << this->_name << " repaired itself for " << amount << " hit points" << std::endl;
}
