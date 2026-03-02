#include "Cat.hpp"

Cat::Cat() : Animal()
{
	std::cout << "Cat default constructor called" << std::endl;
	this->_type = "Cat";
	this->_brain = new Brain();
}

Cat::Cat(const Cat &src) : Animal(src)
{
	std::cout << "Cat copy constructor called" << std::endl;
	this->_brain = new Brain(*src._brain);
}

Cat &Cat::operator=(const Cat &rhs)
{
	std::cout << "Cat assignment operator called" << std::endl;
	Animal::operator=(rhs);
	delete this->_brain;
	this->_brain = new Brain(*rhs._brain);
	return *this;
}

Cat::~Cat()
{
	std::cout << "Cat destructor called" << std::endl;
	delete this->_brain;
}

void Cat::makeSound() const
{
	std::cout << "* meow *" << std::endl;
}

Brain *Cat::getBrain() const
{
	return this->_brain;
}
