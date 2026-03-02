#include "Animal.hpp"
#include "Dog.hpp"
#include "Cat.hpp"

int main(void)
{
	const Animal* j = new Dog();
	const Animal* i = new Cat();

	j->makeSound();
	i->makeSound();

	delete j;
	delete i;

	std::cout << std::endl;
	std::cout << "Deep Copy Test" << std::endl;
	Dog original;
	original.getBrain()->ideas[0] = "I love bones!";
	Dog copy(original);
	std::cout << "Original: " << original.getBrain()->ideas[0] << std::endl;
	std::cout << "Copy:     " << copy.getBrain()->ideas[0] << std::endl;
	copy.getBrain()->ideas[0] = "I love toys!";
	std::cout << "After modifying copy:" << std::endl;
	std::cout << "Original: " << original.getBrain()->ideas[0] << std::endl;
	std::cout << "Copy:     " << copy.getBrain()->ideas[0] << std::endl;

	return 0;
}
