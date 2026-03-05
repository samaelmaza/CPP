#ifndef INTERN_HPP
#define INTERN_HPP

#include <string>
#include "AForm.hpp"

class Intern
{
	public:
		Intern();
		Intern(const Intern &src);
		Intern &operator=(const Intern &rhs);
		~Intern();

		AForm *makeForm(const std::string &name, const std::string &target);

	private:
		AForm *createShrubbery(const std::string &target);
		AForm *createRobotomy(const std::string &target);
		AForm *createPresidential(const std::string &target);
};

#endif
