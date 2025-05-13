#pragma once
#include "Animal.h"
#include "Factory.h"

class Zoo
{
	Animal** animals;
	int size;
	int capacity;

	void resize(int newCap);
	void copyDynamic(const Zoo& other);
	void moveDynamic(Zoo&& other);
	void free();

public:
	Zoo();
	Zoo(const Zoo& other);
	Zoo& operator=(const Zoo& other);
	Zoo(Zoo&& other) noexcept;
	Zoo& operator=(Zoo&& other) noexcept;
	~Zoo();

	void add(const Animal& a);
	void add(Animaltype a);

	void sound() const;
};