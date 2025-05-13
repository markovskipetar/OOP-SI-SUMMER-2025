#include "Zoo.h"

void Zoo::resize(int newCap)
{
    capacity = newCap;
    Animal** temp = new Animal*[capacity];

    for (int i = 0; i < size; i++) {
        temp[i] = animals[i];
    }

    delete[] animals;
    animals = temp;
}

void Zoo::copyDynamic(const Zoo& other)
{
    animals = new Animal * [other.capacity];
    for (int i = 0; i < other.size; i++) {
        animals[i] = other.animals[i]->clone();
    }
}

void Zoo::moveDynamic(Zoo&& other)
{
    animals = other.animals;
    other.animals = nullptr;
}

void Zoo::free()
{
    for (int i = 0; i < size; i++) {
        delete animals[i];
    }

    delete[] animals;
}

Zoo::Zoo()
{
    capacity = 8;
    animals = new Animal * [capacity];
    size = 0;
}

Zoo::Zoo(const Zoo& other)
{
    size = other.size;
    capacity = other.capacity;
    copyDynamic(other);
}

Zoo& Zoo::operator=(const Zoo& other)
{
    if (this != &other) {
        free();
        size = other.size;
        capacity = other.capacity;
        copyDynamic(other);
    }
    return *this;
}

Zoo::Zoo(Zoo&& other) noexcept
{
    size = other.size;
    capacity = other.capacity;
    moveDynamic(std::move(other));
}

Zoo& Zoo::operator=(Zoo&& other) noexcept
{
    if (this != &other) {
        free();
        size = other.size;
        capacity = other.capacity;
        moveDynamic(std::move(other));
    }
    return *this;
}

Zoo::~Zoo()
{
    free();
}

void Zoo::add(const Animal& a)
{
    if (size == capacity) {
        resize(capacity * 2);
    }

    animals[size++] = a.clone();
}

void Zoo::add(Animaltype a)
{
    if (size == capacity) {
        resize(capacity * 2);
    }

    animals[size++] = Factory::create(a);
}

void Zoo::sound() const
{
    for (int i = 0; i < size; i++) {
        animals[i]->sound();
    }
}
