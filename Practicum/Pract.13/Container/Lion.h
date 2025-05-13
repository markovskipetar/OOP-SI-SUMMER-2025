
#pragma once
#include "Animal.h"

class Lion: public Animal
{
public:
	void sound() const override;
	Animal* clone() const override;
};

