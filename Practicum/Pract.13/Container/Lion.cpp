#include "Lion.h"

void Lion::sound() const
{
    std::cout << "Rawr" << std::endl;
}

Animal* Lion::clone() const
{
    return new Lion(*this);
}
