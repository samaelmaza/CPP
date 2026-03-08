#include <iostream>
#include "Array.hpp"

int main(void)
{
	std::cout << "=== Empty array ===" << std::endl;
	Array<int> empty;
	std::cout << "Size: " << empty.size() << std::endl;

	std::cout << std::endl;
	std::cout << "=== Int array of 5 ===" << std::endl;
	Array<int> numbers(5);
	for (unsigned int i = 0; i < numbers.size(); i++)
		numbers[i] = i * 10;
	for (unsigned int i = 0; i < numbers.size(); i++)
		std::cout << "numbers[" << i << "] = " << numbers[i] << std::endl;

	std::cout << std::endl;
	std::cout << "=== Out of bounds ===" << std::endl;
	try
	{
		numbers[10] = 42;
	}
	catch (std::exception &e)
	{
		std::cout << "Exception: " << e.what() << std::endl;
	}

	std::cout << std::endl;
	std::cout << "=== Deep copy test ===" << std::endl;
	Array<int> copy(numbers);
	copy[0] = 999;
	std::cout << "original[0] = " << numbers[0] << std::endl;
	std::cout << "copy[0] = " << copy[0] << std::endl;

	std::cout << std::endl;
	std::cout << "=== String array ===" << std::endl;
	Array<std::string> words(3);
	words[0] = "hello";
	words[1] = "world";
	words[2] = "42";
	for (unsigned int i = 0; i < words.size(); i++)
		std::cout << "words[" << i << "] = " << words[i] << std::endl;

	return 0;
}
