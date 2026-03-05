#include "ShrubberyCreationForm.hpp"

//                                          nom                sign  exec
ShrubberyCreationForm::ShrubberyCreationForm()
	: AForm("ShrubberyCreationForm", 145, 137), _target("default")
{
}

ShrubberyCreationForm::ShrubberyCreationForm(const std::string &target)
	: AForm("ShrubberyCreationForm", 145, 137), _target(target)
{
}

ShrubberyCreationForm::ShrubberyCreationForm(const ShrubberyCreationForm &src)
	: AForm(src), _target(src._target)
{
}

ShrubberyCreationForm &ShrubberyCreationForm::operator=(const ShrubberyCreationForm &rhs)
{
	AForm::operator=(rhs);
	this->_target = rhs._target;
	return *this;
}

ShrubberyCreationForm::~ShrubberyCreationForm()
{
}

// EXECUTEACTION — cree un fichier <target>_shrubbery avec des arbres ASCII dedans
// → Ouvre un fichier avec ofstream (comme tu ouvrirais un fd en C)
// → Ecris des arbres ASCII dedans
// → Ferme le fichier
void ShrubberyCreationForm::executeAction() const
{
	// TODO
}
