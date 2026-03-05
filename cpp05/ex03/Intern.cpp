#include "Intern.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"

Intern::Intern()
{
}

Intern::Intern(const Intern &src)
{
	(void)src;
}

Intern &Intern::operator=(const Intern &rhs)
{
	(void)rhs;
	return *this;
}

Intern::~Intern()
{
}

// Ces 3 fonctions creent chacune un type de formulaire
// Elles retournent un AForm* (new ShrubberyCreationForm(target), etc.)
AForm *Intern::createShrubbery(const std::string &target)
{
	// TODO
}

AForm *Intern::createRobotomy(const std::string &target)
{
	// TODO
}

AForm *Intern::createPresidential(const std::string &target)
{
	// TODO
}

// MAKEFORM — la fonction principale de l'Intern
// → Compare le nom recu avec les 3 noms possibles :
//    "shrubbery creation", "robotomy request", "presidential pardon"
// → Si trouve : affiche "Intern creates <form>" et retourne le formulaire
// → Si pas trouve : affiche une erreur et retourne NULL
//
// IMPORTANT : le sujet interdit les longues chaines de if/else !
// → Utilise un TABLEAU de pointeurs de fonctions (comme un menu)
//
// Indice : tu peux faire un tableau de noms et un tableau de pointeurs
// vers les 3 fonctions create ci-dessus, puis boucler dessus
void Intern::makeForm(const std::string &name, const std::string &target)
{
	// TODO
}
