#include "Bureaucrat.hpp"

// CONSTRUCTEUR PAR DEFAUT
// → Initialise _name a "default" et _grade a 150
Bureaucrat::Bureaucrat()
{
	// TODO: a toi de jouer !
}

// CONSTRUCTEUR AVEC PARAMETRES
// → Initialise _name et _grade
// → Si grade < 1 → throw GradeTooHighException
// → Si grade > 150 → throw GradeTooLowException
Bureaucrat::Bureaucrat(const std::string &name, int grade) : _name(name)
{
	// TODO: verifier le grade et throw si invalide
}

// CONSTRUCTEUR DE COPIE
Bureaucrat::Bureaucrat(const Bureaucrat &src)
{
	// TODO
}

// OPERATEUR D'ASSIGNATION
// Note: _name est const, on ne peut copier que _grade
Bureaucrat &Bureaucrat::operator=(const Bureaucrat &rhs)
{
	// TODO
	return *this;
}

// DESTRUCTEUR
Bureaucrat::~Bureaucrat()
{
}

// GETTERS
const std::string &Bureaucrat::getName() const
{
	// TODO
}

int Bureaucrat::getGrade() const
{
	// TODO
}

// INCREMENT: grade 3 → grade 2 (attention au sens !)
// Doit throw GradeTooHighException si on depasse 1
void Bureaucrat::incrementGrade()
{
	// TODO
}

// DECREMENT: grade 3 → grade 4
// Doit throw GradeTooLowException si on depasse 150
void Bureaucrat::decrementGrade()
{
	// TODO
}

// EXCEPTIONS — what() retourne un message d'erreur
const char *Bureaucrat::GradeTooHighException::what() const throw()
{
	// TODO: retourner un message
}

const char *Bureaucrat::GradeTooLowException::what() const throw()
{
	// TODO: retourner un message
}

// OPERATEUR << : affiche "<name>, bureaucrat grade <grade>."
std::ostream &operator<<(std::ostream &out, const Bureaucrat &b)
{
	// TODO
	return out;
}
