#include "IMateriaSource.hpp"
#include "MateriaSource.hpp"
#include "ICharacter.hpp"
#include "Character.hpp"
#include "Ice.hpp"
#include "Cure.hpp"

int main(void)
{
	std::cout << "Creating Materia Source" << std::endl;
	IMateriaSource *src = new MateriaSource();
	src->learnMateria(new Ice());
	src->learnMateria(new Cure());

	std::cout << std::endl;
	std::cout << "Equipping Cloud" << std::endl;
	ICharacter *cloud = new Character("Cloud");
	AMateria *tmp;
	tmp = src->createMateria("ice");
	cloud->equip(tmp);
	tmp = src->createMateria("cure");
	cloud->equip(tmp);
	tmp = src->createMateria("ice");
	cloud->equip(tmp);
	tmp = src->createMateria("cure");
	cloud->equip(tmp);

	std::cout << std::endl;
	std::cout << "Equipping Sephiroth" << std::endl;
	ICharacter *sephiroth = new Character("Sephiroth");
	tmp = src->createMateria("ice");
	sephiroth->equip(tmp);
	tmp = src->createMateria("ice");
	sephiroth->equip(tmp);

	std::cout << std::endl;
	std::cout << "DUEL: Cloud vs Sephiroth" << std::endl;
	std::cout << "Cloud's turn" << std::endl;
	cloud->use(0, *sephiroth);
	cloud->use(2, *sephiroth);

	std::cout << "Sephiroth strikes back" << std::endl;
	sephiroth->use(0, *cloud);
	sephiroth->use(1, *cloud);

	std::cout << "Cloud heals himself" << std::endl;
	cloud->use(1, *cloud);
	cloud->use(3, *cloud);

	std::cout << std::endl;
	std::cout << "Unequip test" << std::endl;
	cloud->unequip(0);
	cloud->use(0, *sephiroth);

	std::cout << std::endl;
	std::cout << "Unknown materia test" << std::endl;
	tmp = src->createMateria("fire");
	std::cout << "createMateria(\"fire\") = " << tmp << std::endl;

	std::cout << std::endl;
	std::cout << "Deep copy test" << std::endl;
	Character original("Tifa");
	tmp = src->createMateria("cure");
	original.equip(tmp);
	Character copy(original);
	std::cout << "Original uses materia:" << std::endl;
	original.use(0, *sephiroth);
	std::cout << "Copy uses materia:" << std::endl;
	copy.use(0, *sephiroth);

	std::cout << std::endl;
	std::cout << "Cleanup" << std::endl;
	delete cloud;
	delete sephiroth;
	delete src;

	return 0;
}
