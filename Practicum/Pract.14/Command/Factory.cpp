#include "Factory.h"

Command* Factory::create(const char* type) {
	if (strcmp(type, "ratio") == 0) {
		return new RatioCommand();
	}
	else if (strcmp(type, "sum") == 0) {
		return new Sum();
	}

	throw new std::logic_error("Unknown type");
}