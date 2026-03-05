#ifndef AFORM_HPP
#define AFORM_HPP

#include <iostream>
#include <string>
#include <exception>

class Bureaucrat;

class AForm
{
	private:
		const std::string	_name;
		bool				_isSigned;
		const int			_gradeToSign;
		const int			_gradeToExec;
	public:
		AForm();
		AForm(const std::string &name, int gradeToSign, int gradeToExec);
		AForm(const AForm &src);
		AForm &operator=(const AForm &rhs);
		virtual ~AForm();

		const std::string	&getName() const;
		bool				getIsSigned() const;
		int					getGradeToSign() const;
		int					getGradeToExec() const;
		void				beSigned(const Bureaucrat &b);
		void				execute(Bureaucrat const &executor) const;

		class GradeTooHighException : public std::exception
		{
			public:
				const char *what() const throw();
		};

		class GradeTooLowException : public std::exception
		{
			public:
				const char *what() const throw();
		};

		class FormNotSignedException : public std::exception
		{
			public:
				const char *what() const throw();
		};

	protected:
		virtual void	executeAction() const = 0;
};

std::ostream &operator<<(std::ostream &out, const AForm &f);

#endif
