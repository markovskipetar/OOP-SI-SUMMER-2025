#pragma once
#include "Collection.h"

class NormalCollection : public Collection
{
public:
	NormalCollection(int capacity);

	void add(int number) override;
	void remove(int number) override;
	int getSize() const override;
	bool contains(int number)const override;

private:
	void resize() {};
	int capacity;
};

