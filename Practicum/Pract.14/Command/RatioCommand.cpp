#include "RatioCommand.h"

void RatioCommand::execute(const MyClass& mc) const
{
	std::cout << mc.getD() << std::endl;
}
