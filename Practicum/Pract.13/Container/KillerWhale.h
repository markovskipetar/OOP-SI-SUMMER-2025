#pragma once
#include "Animal.h"

class KillerWhale: public Animal
{
public:
	void sound() const override;
	Animal* clone() const override;
};

