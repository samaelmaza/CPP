#include "Dog.hpp"

Dog::Dog() : Animal()
{
	std::cout << "Dog default constructor called" << std::endl;
	this->_type = "Dog";
	this->_brain = new Brain();
}

Dog::Dog(const Dog &src) : Animal(src)
{
	std::cout << "Dog copy constructor called" << std::endl;
	this->_brain = new Brain(*src._brain);
}

Dog &Dog::operator=(const Dog &rhs)
{
	std::cout << "Dog assignment operator called" << std::endl;
	Animal::operator=(rhs);
	delete this->_brain;
	this->_brain = new Brain(*rhs._brain);
	return *this;
}

Dog::~Dog()
{
	std::cout << "Dog destructor called" << std::endl;
	delete this->_brain;
}

void Dog::makeSound() const
{
	std::cout << "* woof *" << std::endl;
}

Brain *Dog::getBrain() const
{
	return this->_brain;
}
