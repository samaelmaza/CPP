#include "Animal.hpp"
#include "Dog.hpp"
#include "Cat.hpp"

int main(void)
{
	std::cout << "Basic Test" << std::endl;
	const Animal* j = new Dog();
	const Animal* i = new Cat();
	delete j;
	delete i;

	std::cout << std::endl;
	std::cout << "Array Test" << std::endl;
	const int size = 4;
	Animal *animals[size];

	for (int k = 0; k < size / 2; k++)
		animals[k] = new Dog();
	for (int k = size / 2; k < size; k++)
		animals[k] = new Cat();
	for (int k = 0; k < size; k++)
		delete animals[k];

	std::cout << std::endl;
	std::cout << "Deep Copy Test" << std::endl;
	Dog original;
	original.getBrain()->ideas[0] = "I love bones!";
	Dog copy(original);
	std::cout << "Original idea: " << original.getBrain()->ideas[0] << std::endl;
	std::cout << "Copy idea:     " << copy.getBrain()->ideas[0] << std::endl;
	copy.getBrain()->ideas[0] = "I love toys!";
	std::cout << "After modifying copy:" << std::endl;
	std::cout << "Original idea: " << original.getBrain()->ideas[0] << std::endl;
	std::cout << "Copy idea:     " << copy.getBrain()->ideas[0] << std::endl;

	return 0;
}
