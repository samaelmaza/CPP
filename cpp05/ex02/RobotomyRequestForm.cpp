#include "RobotomyRequestForm.hpp"

RobotomyRequestForm::RobotomyRequestForm()
	: AForm("RobotomyRequestForm", 72, 45), _target("default")
{
}

RobotomyRequestForm::RobotomyRequestForm(const std::string &target)
	: AForm("RobotomyRequestForm", 72, 45), _target(target)
{
}

RobotomyRequestForm::RobotomyRequestForm(const RobotomyRequestForm &src)
	: AForm(src), _target(src._target)
{
}

RobotomyRequestForm &RobotomyRequestForm::operator=(const RobotomyRequestForm &rhs)
{
	AForm::operator=(rhs);
	this->_target = rhs._target;
	return *this;
}

RobotomyRequestForm::~RobotomyRequestForm()
{
}

// EXECUTEACTION — fait du bruit de perceuse puis robotomise (ou pas)
// → Affiche "* BRRRRR DRILLING NOISES *"
// → 50% de chance : affiche "<target> has been robotomized successfully"
// → 50% de chance : affiche "The robotomy of <target> failed"
// Utilise rand() % 2 pour le 50/50
void RobotomyRequestForm::executeAction() const
{
	// TODO
}
