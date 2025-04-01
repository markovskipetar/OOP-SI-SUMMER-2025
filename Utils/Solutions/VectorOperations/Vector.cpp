#include "Vector.h"

Vector::Vector(const double* components, int size)
{
	setComponents(components, size);
}

Vector::Vector(const Vector& other)
{
	copyFrom(other);
}

Vector& Vector::operator=(const Vector& other)
{
	if ((this != &other) && (size == other.size))
	{
		free();
		copyFrom(other);
	}

	return *this;
}

Vector::~Vector()
{
	free();
}

void Vector::setComponents(const double* components, int size)
{
	if (size <= 0 || !components)
	{
		return;
	}

	this->components = new double[size];
	this->size = size;

	for (int i = 0; i < size; i++)
	{
		this->components[i] = components[i];
	}
}

void Vector::free()
{
	delete[] components;
}

void Vector::copyFrom(const Vector& other)
{
	size = other.size;
	components = new double[size];

	for (int i = 0; i < size; i++)
	{
		components[i] = other.components[i];
	}
}

const double* Vector::getComponents() const
{
	return components;
}

int Vector::getSize() const
{
	return size;
}

void Vector::multiplyByScalar(double scalar)
{
	for (int i = 0; i < size; i++)
	{
		components[i] *= scalar;
	}
}

double Vector::getLength() const
{
	if (!isLengthCalculated)
	{
		double squaredComponentsSum = 0;

		for (int i = 0; i < size; i++)
		{
			squaredComponentsSum += (components[i] * components[i]);
			//squredComponentsSum += (std::pow(components[i], 2));
		}

		length = std::sqrt(squaredComponentsSum);
	}

	return length;
}

Vector Vector::getUnitVector() const
{
	double length = getLength();

	double* unitVectorComponents = new double[size];

	for (int i = 0; i < size; i++)
	{
		unitVectorComponents[i] = (components[i] / length);
	}

	Vector unitVector(unitVectorComponents, size);

	delete[] unitVectorComponents;

	return unitVector;
}

void Vector::writeToBinaryFile(std::ofstream& binaryWriter) const
{
	if (!binaryWriter.is_open())
	{
		return;
	}

	binaryWriter.write((const char*)&size, sizeof(size));
	binaryWriter.write((const char*)components, sizeof(components[0]) * size);
}

void Vector::readFromBinaryFile(std::ifstream& binaryReader)
{
	if (!binaryReader.is_open())
	{
		return;
	}

	binaryReader.read((char*)&size, sizeof(size));

	components = new double[size];

	binaryReader.read((char*)components, sizeof(components[0]) * size);
}

void Vector::print(std::ostream& outputStream) const
{
	outputStream << "(";

	for (int i = 0; i < size; i++)
	{
		outputStream << components[i];

		if (i < size - 1)
		{
			outputStream << ", ";
		}
	}

	outputStream << ")";
}