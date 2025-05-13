#pragma once
#include "Lion.h"
#include "KillerWhale.h"
#include "Dog.h"

enum class Animaltype {
	LION,
	DOG,
	KILLERWHALE
};

class Factory
{
public:
	static Animal* create(Animaltype t);
};

