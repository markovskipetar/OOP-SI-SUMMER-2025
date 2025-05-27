#include "Factory.h"

int main() {
	char buffer[128];
	MyClass mc(1, 2, 3.5);
	while (true) {
		std::cin >> buffer;
		if (strcmp(buffer, "exit") == 0) {
			return 0;
		}

		Command* c = Factory::create(buffer);
		c->execute(mc);
		delete c;
	}
}