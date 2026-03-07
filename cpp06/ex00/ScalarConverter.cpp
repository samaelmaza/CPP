#include "ScalarConverter.hpp"
#include <iomanip>
#include <sstream>

ScalarConverter::ScalarConverter() {}
ScalarConverter::ScalarConverter(const ScalarConverter &src) { (void)src; }
ScalarConverter &ScalarConverter::operator=(const ScalarConverter &rhs) { (void)rhs; return *this; }
ScalarConverter::~ScalarConverter() {}

static bool isPseudoLiteral(const std::string &s)
{
	return (s == "nan" || s == "nanf"
		|| s == "+inf" || s == "-inf"
		|| s == "+inff" || s == "-inff"
		|| s == "inf" || s == "inff");
}

static bool isCharLiteral(const std::string &s)
{
	return (s.length() == 1 && !std::isdigit(s[0]));
}

static bool isFloatLiteral(const std::string &s)
{
	if (s.empty() || s[s.length() - 1] != 'f')
		return false;
	std::string without_f = s.substr(0, s.length() - 1);
	if (without_f.empty())
		return false;
	char *end;
	strtod(without_f.c_str(), &end);
	return (*end == '\0' && without_f.find('.') != std::string::npos);
}

static bool isDoubleLiteral(const std::string &s)
{
	if (s.empty() || s.find('.') == std::string::npos)
		return false;
	char *end;
	strtod(s.c_str(), &end);
	return (*end == '\0');
}

static void printFromDouble(double value)
{
	// CHAR
	if (std::isnan(value) || std::isinf(value) || value < 0 || value > 127)
		std::cout << "char: impossible" << std::endl;
	else if (!std::isprint(static_cast<int>(value)))
		std::cout << "char: Non displayable" << std::endl;
	else
		std::cout << "char: '" << static_cast<char>(value) << "'" << std::endl;

	// INT
	if (std::isnan(value) || std::isinf(value) || value > INT_MAX || value < INT_MIN)
		std::cout << "int: impossible" << std::endl;
	else
		std::cout << "int: " << static_cast<int>(value) << std::endl;

	// FLOAT
	if (value == static_cast<long>(value) && !std::isinf(value) && !std::isnan(value))
		std::cout << "float: " << std::fixed << std::setprecision(1)
			<< static_cast<float>(value) << "f" << std::endl;
	else
		std::cout << "float: " << static_cast<float>(value) << "f" << std::endl;

	// DOUBLE
	if (value == static_cast<long>(value) && !std::isinf(value) && !std::isnan(value))
		std::cout << "double: " << std::fixed << std::setprecision(1) << value << std::endl;
	else
		std::cout << "double: " << value << std::endl;
}

void ScalarConverter::convert(const std::string &literal)
{
	if (literal.empty())
	{
		std::cout << "Error: empty input" << std::endl;
		return;
	}

	if (isPseudoLiteral(literal))
	{
		std::cout << "char: impossible" << std::endl;
		std::cout << "int: impossible" << std::endl;
		if (literal == "nanf" || literal == "+inff" || literal == "-inff" || literal == "inff")
		{
			std::string base = literal.substr(0, literal.length() - 1);
			std::cout << "float: " << base << "f" << std::endl;
			std::cout << "double: " << base << std::endl;
		}
		else
		{
			std::cout << "float: " << literal << "f" << std::endl;
			std::cout << "double: " << literal << std::endl;
		}
		return;
	}

	if (isCharLiteral(literal))
	{
		char c = literal[0];
		printFromDouble(static_cast<double>(c));
		return;
	}

	if (isFloatLiteral(literal))
	{
		double value = strtod(literal.substr(0, literal.length() - 1).c_str(), NULL);
		printFromDouble(value);
		return;
	}

	if (isDoubleLiteral(literal))
	{
		double value = strtod(literal.c_str(), NULL);
		printFromDouble(value);
		return;
	}

	// Int literal
	char *end;
	long lvalue = strtol(literal.c_str(), &end, 10);
	if (*end != '\0')
	{
		std::cout << "Error: invalid input" << std::endl;
		return;
	}
	if (lvalue > INT_MAX || lvalue < INT_MIN)
	{
		std::cout << "Error: int overflow" << std::endl;
		return;
	}
	printFromDouble(static_cast<double>(lvalue));
}
