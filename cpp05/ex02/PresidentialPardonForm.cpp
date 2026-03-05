#include "PresidentialPardonForm.hpp"

PresidentialPardonForm::PresidentialPardonForm()
	: AForm("PresidentialPardonForm", 25, 5), _target("default")
{
}

PresidentialPardonForm::PresidentialPardonForm(const std::string &target)
	: AForm("PresidentialPardonForm", 25, 5), _target(target)
{
}

PresidentialPardonForm::PresidentialPardonForm(const PresidentialPardonForm &src)
	: AForm(src), _target(src._target)
{
}

PresidentialPardonForm &PresidentialPardonForm::operator=(const PresidentialPardonForm &rhs)
{
	AForm::operator=(rhs);
	this->_target = rhs._target;
	return *this;
}

PresidentialPardonForm::~PresidentialPardonForm()
{
}

// EXECUTEACTION — le plus simple des 3 !
// → Affiche "<target> has been pardoned by Zaphod Beeblebrox."
void PresidentialPardonForm::executeAction() const
{
	// TODO
}
