#include "Vector.h"

Vector::Vector(const double* components, int size)
{
	setComponents(components, size);
}

Vector::Vector(const Vector& other)
{
	copyDynamicMemory(other);
}

Vector& Vector::operator=(const Vector& other)
{
	if ((this != &other) && (size == other.size))
	{
		freeDynamicMemory();
		copyDynamicMemory(other);
	}

	return *this;
}

Vector::~Vector()
{
	freeDynamicMemory();
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

void Vector::freeDynamicMemory()
{
	delete[] components;
}

void Vector::copyDynamicMemory(const Vector& other)
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
	double squaredComponentsSum = 0;

	for (int i = 0; i < size; i++)
	{
		squaredComponentsSum += (components[i] * components[i]);
	}

	return std::sqrt(squaredComponentsSum);
}

void Vector::operator+=(double scalar)
{
	for (int i = 0; i < size; i++)
	{
		components[i] += scalar;
	}
}

void Vector::operator*=(double scalar)
{
	for (int i = 0; i < size; i++)
	{
		components[i] *= scalar;
	}
}

Vector& Vector::operator++()
{
	for (int i = 0; i < size; i++)
	{
		components[i]++;
	}

	return *this;
}

Vector Vector::operator++(int) // postfix ++
{
	Vector oldVector(*this);

	++(*this); // calling the prefix ++

	return oldVector;
}

void Vector::operator+=(const Vector& other)
{
	if (size != other.getSize())
	{
		return;
	}

	const double* otherComponents = other.getComponents();

	for (int i = 0; i < size; i++)
	{
		components[i] += otherComponents[i];
	}
}

Vector operator*(const Vector& vector, double scalar) // v * 5
{
	Vector vectorCopy(vector);

	vectorCopy *= scalar;

	return vectorCopy;
}

Vector operator*(double scalar, const Vector& vector) // 5 * v == v * 5
{
	return vector * scalar;
}

Vector operator+(const Vector& lhs, const Vector& rhs)
{
	Vector lhsCopy(lhs);

	lhsCopy += rhs;

	return lhsCopy;
}

bool operator||(const Vector& lhs, const Vector& rhs)
{
	if (lhs.getSize() != rhs.getSize())
	{
		return false;
	}

	const double* lhsComponents = lhs.getComponents();
	const double* rhsComponents = rhs.getComponents();

	double initialRation = lhsComponents[0] / rhsComponents[0];

	const double EPSILON = 0.00000001;

	for (size_t i = 1; i < rhs.getSize(); i++)
	{
		double currentRation = lhsComponents[i] / rhsComponents[i];

		if (std::abs(currentRation - initialRation) > EPSILON)
		{
			return false;
		}
	}

	return true;
}

std::ostream& operator<<(std::ofstream& outputStream, const Vector& vector)
{
	const double* components = vector.getComponents();
	int size = vector.getSize();

	for (int i = 0; i < size; i++)
	{
		outputStream << components[i] << " ";
	}

	return outputStream;
}

std::istream& operator>>(std::istream& inputStream, const Vector& vector)
{
	int size = vector.getSize();

	for (int i = 0; i < size; i++)
	{
		// vector.components is acessible because operator>> is friend of Vector
		inputStream >> vector.components[i]; // 
	}

	return inputStream;
}
