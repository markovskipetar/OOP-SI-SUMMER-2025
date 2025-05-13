#include "Factory.h"

Animal* Factory::create(Animaltype t)
{
	switch (t) {
	case Animaltype::LION:
		return new Lion();
	case Animaltype::DOG:
		return new Dog();
	case Animaltype::KILLERWHALE:
		return new KillerWhale();
	default:
		throw std::logic_error("Unknow type");
	}
}