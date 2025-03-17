#include <iostream>
#pragma warning(disable:4996)

struct Item {
	char name[30];
	int code;

	void print() const {
		std::cout << name<<" " << code << std::endl;
	}

	Item() {
		strcpy(name, "Unknown");
		code = -1;
	}

	Item(const char* name, int code) {
		strcpy(this->name, name);
		this->code = code;
	}
};

class Order {
private:
	Item* items;
	int size;
	int capacity;

	int roundToPowerOfTwo(int num) const {
		num--;
		num |= num >> 1;
		num |= num >> 2;
		num |= num >> 4;
		num |= num >> 8;
		num |= num >> 16;
		num++;
		return num;
	}

	void resize(int newCap) {
		capacity = newCap;

		Item* temp = new Item[capacity];

		for (int i = 0; i < size; i++) {
			temp[i] = items[i];
		}

		delete[] items;

		items = temp;
	}

	void shiftLeft(int index) {
		for (int i = index; i < size - 1; i++) {
			items[i] = items[i + 1];
		}
	}

public:
	Order() {
		items = new Item[2];
		size = 0;
		capacity = 2;
	}

	Order(const Item* items, int size) {
		capacity = roundToPowerOfTwo(size);
		this->size = size;
		this->items = new Item[capacity];

		for (int i = 0; i < size; i++) {
			this->items[i] = items[i];
		}
	}

	void addItem(const Item& i) {
		if (size == capacity) {
			resize(capacity * 2);
		}

		items[size++] = i;
	}

	void removeItem(int index) {
		if (index >= size) {
			return;
		}

		shiftLeft(index);

		size--;
	}

	void print() const {
		for (int i = 0; i < size; i++) {
			items[i].print();
		}
	}

	~Order() {
		delete[] items;
	}
};

int main() {
	Order o;

	Item i1("aa", 12);
	Item i2("bbbbb", 11214);
	Item i3("momo", 6);
	Item i4("boris", 12);

	o.addItem(i1);
	o.addItem(i2);
	o.addItem(i3);
	o.addItem(i4);

	o.removeItem(2);

	o.print();
}