#include "Bureaucrat.hpp"
#include "AForm.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"

int main(void)
{
	srand(time(NULL));

	std::cout << "=== Presidential Pardon ===" << std::endl;
	try
	{
		Bureaucrat president("President", 1);
		PresidentialPardonForm pardon("Arthur Dent");
		president.signForm(pardon);
		president.executeForm(pardon);
	}
	catch (std::exception &e)
	{
		std::cout << "Exception: " << e.what() << std::endl;
	}

	std::cout << std::endl;
	std::cout << "=== Robotomy Request ===" << std::endl;
	try
	{
		Bureaucrat boss("Boss", 1);
		RobotomyRequestForm robo("Bender");
		boss.signForm(robo);
		boss.executeForm(robo);
		boss.executeForm(robo);
	}
	catch (std::exception &e)
	{
		std::cout << "Exception: " << e.what() << std::endl;
	}

	std::cout << std::endl;
	std::cout << "=== Shrubbery Creation ===" << std::endl;
	try
	{
		Bureaucrat gardener("Gardener", 1);
		ShrubberyCreationForm shrub("home");
		gardener.signForm(shrub);
		gardener.executeForm(shrub);
	}
	catch (std::exception &e)
	{
		std::cout << "Exception: " << e.what() << std::endl;
	}

	std::cout << std::endl;
	std::cout << "=== Execute without signing ===" << std::endl;
	try
	{
		Bureaucrat boss("Boss", 1);
		PresidentialPardonForm pardon("Ford");
		boss.executeForm(pardon);
	}
	catch (std::exception &e)
	{
		std::cout << "Exception: " << e.what() << std::endl;
	}

	std::cout << std::endl;
	std::cout << "=== Grade too low to execute ===" << std::endl;
	try
	{
		Bureaucrat intern("Intern", 150);
		ShrubberyCreationForm shrub("garden");
		Bureaucrat boss("Boss", 1);
		boss.signForm(shrub);
		intern.executeForm(shrub);
	}
	catch (std::exception &e)
	{
		std::cout << "Exception: " << e.what() << std::endl;
	}

	return 0;
}
