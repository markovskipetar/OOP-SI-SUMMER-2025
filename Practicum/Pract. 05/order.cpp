#include <iostream>
#pragma warning(disable:4996)


namespace CONSTANTS
{
	constexpr size_t NAME_MAX_SIZE = 30;
}

struct Item 
{
	char name[CONSTANTS::NAME_MAX_SIZE + 1] = "Unknown";
	int code = 0;

	Item() = default;

	Item(const char* name, int code)
	{
		strcpy(this->name, name);
		this->code = code;
	}

	void print() const 
	{
		std::cout << name << " " << code << std::endl;
	}

};

class Order
{
public:

	Order(): number(0), size(0), capacity(2)     
	{
		items = new Item[capacity];
	}

	Order(unsigned number, const Item* items, size_t itemsSize) :
		number(number), size(size)
	{
		setItems(items, itemsSize);
	}

	void addItem(const Item& item)
	{

		if (size >= capacity)
		{
			resize(2 * capacity);
		}

		items[size++] = item;
	}

	void removeItem(size_t index)
	{
		if (index >= size)
		{
			return;
		}

		std::swap(items[index], items[size - 1]);
		size--;
	}

	void print() const
	{
		std::cout << "[Order Number]: " << number << std::endl;
		for (size_t i = 0; i < size; i++)
		{
			items[i].print();
		}

	}

	~Order()
	{
		free();
	}

private:

	int roundToPowerOfTwo(int num) const
	{
		num--;
		num |= num >> 1;
		num |= num >> 2;
		num |= num >> 4;
		num |= num >> 8;
		num |= num >> 16;
		num++;

		return num;
	}

	void setItems(const Item* items, size_t itemsSize)
	{

		if (!items || itemsSize == 0 || this->items == items)
		{
			return;
		}

		this->capacity = roundToPowerOfTwo(itemsSize);
		this->size = itemsSize;

		//delete[] this->items for reusability
		this->items = new Item[this->capacity];

		for (size_t i = 0; i < itemsSize; i++)
		{
			this->items[i] = items[i];
		}

	}

	void resize(size_t newCap)
	{
		capacity = newCap;
		
		Item* newItems = new Item[capacity];
		for (size_t i = 0; i < size; i++)
		{
			newItems[i] = items[i];
		}

		delete[] items;
		items = newItems;
		newItems = nullptr;
	}

	void free()
	{
		number = 0;

		delete[] items;
		size = 0;
		capacity = 0;
	}

	unsigned number = 0;
	Item* items = nullptr;
	size_t size = 0;
	size_t capacity = 0;
};

int main()
{
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

	return 0;
}
