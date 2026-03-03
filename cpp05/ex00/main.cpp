#include "Bureaucrat.hpp"

int main(void)
{
	std::cout << "=== Valid Bureaucrat ===" << std::endl;
	try
	{
		Bureaucrat b("Sam", 42);
		std::cout << b << std::endl;
	}
	catch (std::exception &e)
	{
		std::cout << "Exception: " << e.what() << std::endl;
	}

	std::cout << std::endl;
	std::cout << "=== Grade too high (0) ===" << std::endl;
	try
	{
		Bureaucrat b("TooHigh", 0);
		std::cout << b << std::endl;
	}
	catch (std::exception &e)
	{
		std::cout << "Exception: " << e.what() << std::endl;
	}

	std::cout << std::endl;
	std::cout << "=== Grade too low (151) ===" << std::endl;
	try
	{
		Bureaucrat b("TooLow", 151);
		std::cout << b << std::endl;
	}
	catch (std::exception &e)
	{
		std::cout << "Exception: " << e.what() << std::endl;
	}

	std::cout << std::endl;
	std::cout << "=== Increment from 1 ===" << std::endl;
	try
	{
		Bureaucrat b("Boss", 1);
		std::cout << b << std::endl;
		b.incrementGrade();
	}
	catch (std::exception &e)
	{
		std::cout << "Exception: " << e.what() << std::endl;
	}

	std::cout << std::endl;
	std::cout << "=== Decrement from 150 ===" << std::endl;
	try
	{
		Bureaucrat b("Intern", 150);
		std::cout << b << std::endl;
		b.decrementGrade();
	}
	catch (std::exception &e)
	{
		std::cout << "Exception: " << e.what() << std::endl;
	}

	std::cout << std::endl;
	std::cout << "=== Normal increment/decrement ===" << std::endl;
	try
	{
		Bureaucrat b("Normal", 75);
		std::cout << b << std::endl;
		b.incrementGrade();
		std::cout << "After increment: " << b << std::endl;
		b.decrementGrade();
		std::cout << "After decrement: " << b << std::endl;
	}
	catch (std::exception &e)
	{
		std::cout << "Exception: " << e.what() << std::endl;
	}

	return 0;
}
