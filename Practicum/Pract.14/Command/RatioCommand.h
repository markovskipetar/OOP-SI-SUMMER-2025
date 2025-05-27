#pragma once
#include "Command.h"

class RatioCommand: public Command
{
public:
	void execute(const MyClass& mc) const override;
};

