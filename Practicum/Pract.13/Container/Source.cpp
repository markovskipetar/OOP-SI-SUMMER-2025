#include "Zoo.h"

int main() {
	Zoo z;
	Lion l;
	KillerWhale kw;

	z.add(l);
	z.add(kw);
	z.add(l);
	z.add(Animaltype::DOG);

	z.sound();
}