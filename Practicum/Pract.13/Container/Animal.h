#pragma once
#include <iostream>

class Animal
{
public:
	virtual Animal* clone() const = 0;
	virtual void sound() const = 0;
	virtual ~Animal() = default;
};

