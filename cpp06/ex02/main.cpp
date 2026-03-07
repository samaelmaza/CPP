#include "Base.hpp"
#include <iostream>
#include <cstdlib>

Base *generate(void)
{
	int random = rand() % 3;
	if (random == 0)
		return new A();
	else if (random == 1)
		return new B();
	else
		return new C();
}

void identify(Base *p)
{
	if (dynamic_cast<A *>(p))
		std::cout << "A" << std::endl;
	else if (dynamic_cast<B *>(p))
		std::cout << "B" << std::endl;
	else if (dynamic_cast<C *>(p))
		std::cout << "C" << std::endl;
}

// Identifies the type via reference (dynamic_cast throws on failure, so use try/catch)
void identify(Base &p)
{
	try
	{
		A &a = dynamic_cast<A &>(p);
		(void)a;
		std::cout << "A" << std::endl;
	}
	catch (...)
	{
		try
		{
			B &b = dynamic_cast<B &>(p);
			(void)b;
			std::cout << "B" << std::endl;
		}
		catch (...)
		{
			try
			{
				C &c = dynamic_cast<C &>(p);
				(void)c;
				std::cout << "C" << std::endl;
			}
			catch (...)
			{
				std::cout << "Unknown" << std::endl;
			}
		}
	}
}

int main(void)
{
	srand(time(NULL));

	std::cout << "=== Test 1 ===" << std::endl;
	Base *obj1 = generate();
	identify(obj1);
	identify(*obj1);

	std::cout << std::endl;
	std::cout << "=== Test 2 ===" << std::endl;
	Base *obj2 = generate();
	identify(obj2);
	identify(*obj2);

	std::cout << std::endl;
	std::cout << "=== Test 3 ===" << std::endl;
	Base *obj3 = generate();
	identify(obj3);
	identify(*obj3);

	delete obj1;
	delete obj2;
	delete obj3;

	return 0;
}
