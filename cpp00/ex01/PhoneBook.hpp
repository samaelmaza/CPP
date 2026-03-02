#ifndef PHONEBOOK_HPP
# define PHONEBOOK_HPP

# include "Contact.hpp"
# include <iomanip>
# include <cstdlib>

class PhoneBook
{
	private:
		Contact	_contacts[8];
		int		_index;
		int		_nbContact;
		std::string	_getInput(std::string prompt) const;
		std::string _formatColumn(std::string str) const;
		bool _isValid(std::string str) const;

	public:
		PhoneBook();
		~PhoneBook();
		void		add();
		void		search();
};

#endif
