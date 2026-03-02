#include "PhoneBook.hpp"

PhoneBook::PhoneBook()
{
	this->_index = 0;
	this->_nbContact = 0;
}

PhoneBook::~PhoneBook()
{
}

std::string	PhoneBook::_getInput(std::string prompt) const
{
	std::string str;
	while(true)
	{
		std::cout << prompt << std::flush;
		if(!std::getline(std::cin, str))
			break;
		if(!str.empty())
			return str;
		else
			std::cout << "Fiel cannot be empty!" << std::endl;
	}
	return "";
}


void PhoneBook::add()
{
	this->_contacts[this->_index].setFirstName(this->_getInput("Enter First Name : "));
	this->_contacts[this->_index].setLastName(this->_getInput("Enter Last Name : "));
	this->_contacts[this->_index].setNickName(this->_getInput("Enter Nickname : "));
	this->_contacts[this->_index].setPhoneNumber(this->_getInput("Enter Phone Number : "));
	this->_contacts[this->_index].setDarkestSecret(this->_getInput("Enter Darkest Secret : "));
	this->_index++;
	if(this->_index > 7)
		this->_index = 0;
	if(this->_nbContact < 8)
		this->_nbContact++;
	std::cout << "Contact added successfully!" << std::endl;
}

std::string PhoneBook::_formatColumn(std::string str) const
{
	if(str.length() > 10)
		str = str.substr(0, 9) + ".";
	return str;
}

bool PhoneBook::_isValid(std::string str) const
{
	if(str.empty())
		return false;
	int i = 0;
	while(i < (int)str.length())
	{
		if(!isdigit(str[i]))
			return false;
		i++;
	}
	int index = atoi(str.c_str());
	if(index >= 0 && index < _nbContact)
		return true;
	return false;
}

void PhoneBook::search()
{
	std::cout << " ___________________________________________ " << std::endl;
	std::cout << "|     Index|First Name| Last Name|  Nickname|" << std::endl;
	std::cout << "|----------|----------|----------|----------|" << std::endl;
	int i = 0;
	while(i < this->_nbContact)
	{
		std::cout << "|" << std::setw(10) << i;
		std::cout << "|" << std::setw(10) << _formatColumn(this->_contacts[i].getFirstName());
		std::cout << "|" << std::setw(10) << _formatColumn(this->_contacts[i].getLastName());
		std::cout << "|" << std::setw(10) << _formatColumn(this->_contacts[i].getNickName());
		std::cout << "|" << std::endl;
		i++;
	}
	std::cout << " ___________________________________________ " << std::endl;
	std::string indexNb = "";
	std::cout << "Enter index to view details: " << std::flush;
	if(std::getline(std::cin, indexNb) && _isValid(indexNb))
	{
		int index = std::atoi(indexNb.c_str());
		std::cout << "\n--- Contact #" << index << " ---" << std::endl;
		std::cout << "First Name: " << _contacts[index].getFirstName() << std::endl;
		std::cout << "Last Name: " << _contacts[index].getLastName() << std::endl;
		std::cout << "Nickname: " << _contacts[index].getNickName() << std::endl;
		std::cout << "Phone Number: " << _contacts[index].getPhoneNumber() << std::endl;
		std::cout << "Darkest Secret: " << _contacts[index].getDarkestSecret() << std::endl;
	}
	else
		std::cout << "Invalid index!" << std::endl;
}
