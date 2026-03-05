#include "AForm.hpp"
#include "Bureaucrat.hpp"

AForm::AForm() : _name("default"), _isSigned(false), _gradeToSign(150), _gradeToExec(150)
{
}

AForm::AForm(const std::string &name, int gradeToSign, int gradeToExec)
	: _name(name), _isSigned(false), _gradeToSign(gradeToSign), _gradeToExec(gradeToExec)
{
	if (gradeToSign < 1 || gradeToExec < 1)
		throw GradeTooHighException();
	if (gradeToSign > 150 || gradeToExec > 150)
		throw GradeTooLowException();
}

AForm::AForm(const AForm &src)
	: _name(src._name), _isSigned(src._isSigned),
	  _gradeToSign(src._gradeToSign), _gradeToExec(src._gradeToExec)
{
}

AForm &AForm::operator=(const AForm &rhs)
{
	if (this != &rhs)
		this->_isSigned = rhs._isSigned;
	return *this;
}

AForm::~AForm()
{
}

const std::string &AForm::getName() const
{
	return this->_name;
}

bool AForm::getIsSigned() const
{
	return this->_isSigned;
}

int AForm::getGradeToSign() const
{
	return this->_gradeToSign;
}

int AForm::getGradeToExec() const
{
	return this->_gradeToExec;
}

void AForm::beSigned(const Bureaucrat &b)
{
	if (b.getGrade() > this->_gradeToSign)
		throw GradeTooLowException();
	this->_isSigned = true;
}

void AForm::execute(Bureaucrat const &executor) const
{
	if (_isSigned == false)
		throw FormNotSignedException();
	if (executor.getGrade() > _gradeToExec)
		throw GradeTooLowException();
	executeAction();
}

const char *AForm::GradeTooHighException::what() const throw()
{
	return "Grade is too high!";
}

const char *AForm::GradeTooLowException::what() const throw()
{
	return "Grade is too low!";
}

const char *AForm::FormNotSignedException::what() const throw()
{
	return "Form is not signed!";
}

std::ostream &operator<<(std::ostream &out, const AForm &f)
{
	out << f.getName() << ", form grade to sign " << f.getGradeToSign()
		<< ", grade to exec " << f.getGradeToExec()
		<< ", signed: " << f.getIsSigned() << ".";
	return out;
}
