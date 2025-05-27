#pragma once
#include "RatioCommand.h"
#include "Sum.h"

class Factory
{
public:
	static Command* create(const char* type);
};

