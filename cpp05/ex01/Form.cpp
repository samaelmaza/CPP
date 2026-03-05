#include "Form.hpp"
#include "Bureaucrat.hpp"

Form::Form() : _name("default"), _isSigned(false), _gradeToSign(150), _gradeToExec(150)
{
}

Form::Form(const std::string &name, int gradeToSign, int gradeToExec)
	: _name(name), _isSigned(false), _gradeToSign(gradeToSign), _gradeToExec(gradeToExec)
{
	if (gradeToSign < 1 || gradeToExec < 1)
		throw GradeTooHighException();
	if (gradeToSign > 150 || gradeToExec > 150)
		throw GradeTooLowException();
}

Form::Form(const Form &src)
	: _name(src._name), _isSigned(src._isSigned),
	  _gradeToSign(src._gradeToSign), _gradeToExec(src._gradeToExec)
{
}

Form &Form::operator=(const Form &rhs)
{
	if (this != &rhs)
		this->_isSigned = rhs._isSigned;
	return *this;
}

Form::~Form()
{
}

const std::string &Form::getName() const
{
	return this->_name;
}

bool Form::getIsSigned() const
{
	return this->_isSigned;
}

int Form::getGradeToSign() const
{
	return this->_gradeToSign;
}

int Form::getGradeToExec() const
{
	return this->_gradeToExec;
}

void Form::beSigned(const Bureaucrat &b)
{
	if (b.getGrade() > this->_gradeToSign)
		throw GradeTooLowException();
	this->_isSigned = true;
}

const char *Form::GradeTooHighException::what() const throw()
{
	return "Grade is too high!";
}

const char *Form::GradeTooLowException::what() const throw()
{
	return "Grade is too low!";
}

std::ostream &operator<<(std::ostream &out, const Form &f)
{
	out << f.getName() << ", form grade to sign " << f.getGradeToSign()
		<< ", grade to exec " << f.getGradeToExec()
		<< ", signed: " << f.getIsSigned() << ".";
	return out;
}
