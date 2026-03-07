#include "Serializer.hpp"

Serializer::Serializer() {}
Serializer::Serializer(const Serializer &src) { (void)src; }
Serializer &Serializer::operator=(const Serializer &rhs) { (void)rhs; return *this; }
Serializer::~Serializer() {}

// Converts a Data* pointer to a uintptr_t integer
uintptr_t Serializer::serialize(Data *ptr)
{
	return reinterpret_cast<uintptr_t>(ptr);
}

// Converts a uintptr_t integer back to a Data* pointer
Data *Serializer::deserialize(uintptr_t raw)
{
	return reinterpret_cast<Data *>(raw);
}
