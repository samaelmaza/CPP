#include <iostream>
#include <vector>
#include <list>
#include "easyfind.hpp"

int main(void)
{
	std::cout << "=== Vector Test ===" << std::endl;
	std::vector<int> vec;
	vec.push_back(10);
	vec.push_back(20);
	vec.push_back(30);
	vec.push_back(40);

	try
	{
		std::vector<int>::iterator it = easyfind(vec, 30);
		std::cout << "Found in vector: " << *it << std::endl;
		
		it = easyfind(vec, 99); // Should throw
		std::cout << "Found in vector: " << *it << std::endl;
	}
	catch (std::exception &e)
	{
		std::cout << "Error: " << e.what() << std::endl;
	}

	std::cout << "\n=== List Test ===" << std::endl;
	std::list<int> lst;
	lst.push_back(1);
	lst.push_back(2);
	lst.push_back(3);

	try
	{
		std::list<int>::iterator it = easyfind(lst, 2);
		std::cout << "Found in list: " << *it << std::endl;
		
		it = easyfind(lst, 42); // Should throw
		std::cout << "Found in list: " << *it << std::endl;
	}
	catch (std::exception &e)
	{
		std::cout << "Error: " << e.what() << std::endl;
	}

	return 0;
}
