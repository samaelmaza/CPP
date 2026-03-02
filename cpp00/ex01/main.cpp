#include "PhoneBook.hpp"

int main()
{
	PhoneBook myPhonebook;
	std::string command;

	std::cout << "Commands: ADD, SEARCH, EXIT" << std::endl;
	while(true)
	{
		std::cout << '>' << std::flush;
		if(!std::getline(std::cin, command))
			break;
		if(command == "ADD")
			myPhonebook.add();
		else if(command == "SEARCH")
			myPhonebook.search();
		else if(command == "EXIT")
		{
			std::cout << "Goodbye !" << std::endl;
			break;
		}
		else
			std::cout << "Unknown command" << std::endl;
	}
	return 0;
}
