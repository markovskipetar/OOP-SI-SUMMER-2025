#pragma once
#include <cmath>
#include <fstream>

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
	Vector getUnitVector() const;

	void writeToBinaryFile(std::ofstream& binaryWriter) const;
	void readFromBinaryFile(std::ifstream& binaryReader);

	void print(std::ostream& outputStream) const;

private:
	void setComponents(const double* components, int size);

	void copyFrom(const Vector& other);
	void free();

	double* components = nullptr;
	int size = -1;

	mutable double length = 0;
	bool isLengthCalculated = false;
};

