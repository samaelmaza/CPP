#ifndef FRAGTRAP_HPP
#define FRAGTRAP_HPP

#include "ClapTrap.hpp"

//                  ↓↓↓↓↓↓↓ VIRTUAL ici aussi !
class FragTrap : virtual public ClapTrap
{
	public:
		FragTrap();
		FragTrap(std::string name);
		FragTrap(const FragTrap &src);
		FragTrap &operator=(const FragTrap &rhs);
		~FragTrap();
		void highFivesGuys(void);
};

#endif
