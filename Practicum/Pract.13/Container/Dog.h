#pragma once
#include "Animal.h"
class Dog: public Animal
{
public:
	void sound() const override;
	Animal* clone() const override;
};

