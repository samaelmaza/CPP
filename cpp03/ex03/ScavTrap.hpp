#ifndef SCAVTRAP_HPP
#define SCAVTRAP_HPP

#include "ClapTrap.hpp"

//                  ↓↓↓↓↓↓↓ VIRTUAL = la clé pour le problème du diamant !
class ScavTrap : virtual public ClapTrap
{
	public:
		ScavTrap();
		ScavTrap(std::string name);
		ScavTrap(const ScavTrap &src);
		ScavTrap &operator=(const ScavTrap &rhs);
		~ScavTrap();
		void attack(const std::string &target);
		void guardGate();
};

#endif
