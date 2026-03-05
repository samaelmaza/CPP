#include "Bureaucrat.hpp"
#include "Form.hpp"

int main(void)
{
	std::cout << "=== Create a valid form ===" << std::endl;
	try
	{
		Form f("Tax Form", 50, 25);
		std::cout << f << std::endl;
	}
	catch (std::exception &e)
	{
		std::cout << "Exception: " << e.what() << std::endl;
	}

	std::cout << std::endl;
	std::cout << "=== Form with invalid grade ===" << std::endl;
	try
	{
		Form f("Bad Form", 0, 25);
	}
	catch (std::exception &e)
	{
		std::cout << "Exception: " << e.what() << std::endl;
	}

	std::cout << std::endl;
	std::cout << "=== Sign with high enough grade ===" << std::endl;
	try
	{
		Bureaucrat b("Boss", 1);
		Form f("Tax Form", 50, 25);
		b.signForm(f);
		std::cout << f << std::endl;
	}
	catch (std::exception &e)
	{
		std::cout << "Exception: " << e.what() << std::endl;
	}

	std::cout << std::endl;
	std::cout << "=== Sign with too low grade ===" << std::endl;
	try
	{
		Bureaucrat b("Intern", 100);
		Form f("Tax Form", 50, 25);
		b.signForm(f);
	}
	catch (std::exception &e)
	{
		std::cout << "Exception: " << e.what() << std::endl;
	}

	return 0;
}
