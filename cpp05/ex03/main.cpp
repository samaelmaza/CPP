#include "Bureaucrat.hpp"
#include "AForm.hpp"
#include "Intern.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"

int main(void)
{
	srand(time(NULL));
	Intern intern;

	std::cout << "=== Create valid forms ===" << std::endl;
	AForm *rrf = intern.makeForm("robotomy request", "Bender");
	AForm *ppf = intern.makeForm("presidential pardon", "Ford");
	AForm *scf = intern.makeForm("shrubbery creation", "home");

	std::cout << std::endl;
	std::cout << "=== Create unknown form ===" << std::endl;
	AForm *bad = intern.makeForm("coffee request", "Boss");

	std::cout << std::endl;
	std::cout << "=== Sign and execute ===" << std::endl;
	Bureaucrat boss("President", 1);
	if (rrf)
	{
		boss.signForm(*rrf);
		boss.executeForm(*rrf);
	}
	if (ppf)
	{
		boss.signForm(*ppf);
		boss.executeForm(*ppf);
	}

	std::cout << std::endl;
	std::cout << "=== Cleanup ===" << std::endl;
	delete rrf;
	delete ppf;
	delete scf;
	delete bad;

	return 0;
}
