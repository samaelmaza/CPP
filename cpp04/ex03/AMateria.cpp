#include "AMateria.hpp"
#include "ICharacter.hpp"

AMateria::AMateria() : _type("default") {}

AMateria::AMateria(std::string const &type) : _type(type) {}

AMateria::AMateria(const AMateria &src) : _type(src._type) {}

AMateria &AMateria::operator=(const AMateria &rhs)
{
	(void)rhs;
	return *this;
}

AMateria::~AMateria() {}

std::string const &AMateria::getType() const
{
	return this->_type;
}

void AMateria::use(ICharacter &target)
{
	(void)target;
}
