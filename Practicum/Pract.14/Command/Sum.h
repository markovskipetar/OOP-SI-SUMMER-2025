#pragma once
#include "Command.h"

class Sum: public Command
{
public:
	void execute(const MyClass& mc) const override;
};

