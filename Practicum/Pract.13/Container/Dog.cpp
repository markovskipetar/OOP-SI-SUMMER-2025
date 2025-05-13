#include "Dog.h"

void Dog::sound() const
{
    std::cout << "Wuf wuf" << std::endl;
}

Animal* Dog::clone() const
{
    return new Dog(*this);
}
