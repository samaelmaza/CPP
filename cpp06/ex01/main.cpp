#include "Serializer.hpp"
#include <iostream>

int main(void)
{
	Data data;
	data.name = "Sam";
	data.age = 42;

	std::cout << "=== Original ===" << std::endl;
	std::cout << "Address: " << &data << std::endl;
	std::cout << "Name: " << data.name << std::endl;
	std::cout << "Age: " << data.age << std::endl;

	std::cout << std::endl;
	std::cout << "=== Serialize ===" << std::endl;
	uintptr_t raw = Serializer::serialize(&data);
	std::cout << "Raw value: " << raw << std::endl;

	std::cout << std::endl;
	std::cout << "=== Deserialize ===" << std::endl;
	Data *back = Serializer::deserialize(raw);
	std::cout << "Address: " << back << std::endl;
	std::cout << "Name: " << back->name << std::endl;
	std::cout << "Age: " << back->age << std::endl;

	std::cout << std::endl;
	if (back == &data)
		std::cout << "Pointers match! ✅" << std::endl;
	else
		std::cout << "Pointers DON'T match! ❌" << std::endl;

	return 0;
}
