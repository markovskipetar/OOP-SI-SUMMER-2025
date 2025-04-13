#pragma once
#include <cmath>
#include <fstream>
#include <iostream>

class Vector
{
public:
	Vector() = default;
	Vector(const double* components, int size);
	Vector(const Vector& other);
	Vector& operator=(const Vector& other);
	~Vector();

	double getLength() const;
	const double* getComponents() const;
	int getSize() const;

	void multiplyByScalar(double scalar);

	void operator+=(double scalar);
	void operator+=(const Vector& other);
	void operator*=(double scalar);
	Vector& operator++();
	Vector operator++(int);


	friend std::istream& operator>> (std::istream& outputStream, const Vector& vector);

private:
	void setComponents(const double* components, int size);

	void copyDynamicMemory(const Vector& other);
	void freeDynamicMemory();

	double* components = nullptr;
	int size = 0;
};

Vector operator*(const Vector& vector, double scalar);
Vector operator*(double scalar, const Vector& vector);
Vector operator+(const Vector& lhs, const Vector& rhs);
bool operator||(const Vector& lhs, const Vector& rhs);

std::ostream& operator<< (std::ofstream& outputStream, const Vector& vector);
std::istream& operator>> (std::istream& outputStream, const Vector& vector);