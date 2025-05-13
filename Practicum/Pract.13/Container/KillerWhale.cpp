#include "KillerWhale.h"

void KillerWhale::sound() const
{
    std::cout << "..." << std::endl;
}

Animal* KillerWhale::clone() const
{
    return new KillerWhale(*this);
}
