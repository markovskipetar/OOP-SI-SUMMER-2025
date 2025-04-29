#pragma once
#include "Collection.h"

class IntervalCollection : public Collection
{
public:
	IntervalCollection(int start, int end);

	void add(int number) override;
	void remove(int number) override;
	int getSize() const override;
	bool contains(int number)const override;

private:
	int start;
	int end;
};