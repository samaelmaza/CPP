#include "Character.hpp"

Character::Character() : _name("default")
{
	for (int i = 0; i < 4; i++)
		this->_inventory[i] = 0;
}

Character::Character(std::string name) : _name(name)
{
	for (int i = 0; i < 4; i++)
		this->_inventory[i] = 0;
}

Character::Character(const Character &src) : _name(src._name)
{
	for (int i = 0; i < 4; i++)
	{
		if (src._inventory[i])
			this->_inventory[i] = src._inventory[i]->clone();
		else
			this->_inventory[i] = 0;
	}
}

Character &Character::operator=(const Character &rhs)
{
	this->_name = rhs._name;
	for (int i = 0; i < 4; i++)
	{
		delete this->_inventory[i];
		if (rhs._inventory[i])
			this->_inventory[i] = rhs._inventory[i]->clone();
		else
			this->_inventory[i] = 0;
	}
	return *this;
}

Character::~Character()
{
	for (int i = 0; i < 4; i++)
		delete this->_inventory[i];
}

std::string const &Character::getName() const
{
	return this->_name;
}

void Character::equip(AMateria *m)
{
	if (!m)
		return;
	for (int i = 0; i < 4; i++)
	{
		if (!this->_inventory[i])
		{
			this->_inventory[i] = m;
			return;
		}
	}
}

void Character::unequip(int idx)
{
	if (idx < 0 || idx >= 4 || !this->_inventory[idx])
		return;
	this->_inventory[idx] = 0;
}

void Character::use(int idx, ICharacter &target)
{
	if (idx < 0 || idx >= 4 || !this->_inventory[idx])
		return;
	this->_inventory[idx]->use(target);
}
