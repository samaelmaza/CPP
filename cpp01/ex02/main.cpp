#include <iostream>
#include <string>

int main()
{
	std::string var = "HI THIS IS BRAIN";
	std::string *ptr = &var;
	std::string &ref = var;

	std::cout << "Adress var : " << &var << std::endl;
	std::cout << "Adress ptr : " << ptr << std::endl;
	std::cout << "Adress ref : " << &ref << std::endl;

	std::cout << std::endl;

	std::cout << "Value var : " << var << std::endl;
	std::cout << "Value ptr : " << *ptr << std::endl;
	std::cout << "Value ref : " << ref << std::endl;

	return 0;
}
