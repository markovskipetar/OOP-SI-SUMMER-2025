#pragma once
#include "MyClass.h"
class Command
{
public:
	virtual void execute(const MyClass& mc) const = 0;
	virtual ~Command() = default;
};