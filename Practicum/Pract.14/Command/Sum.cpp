#include "Sum.h"

void Sum::execute(const MyClass& mc) const
{
	std::cout << mc.getA() + mc.getB() << std::endl;;
}