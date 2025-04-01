#include <iostream>
#include "VectorOperations.h"
#include "VectorOperations.h"

void printVectorInfo(const Vector& vector)
{
	std::cout << "Vector components: ";
	vector.print(std::cout);
	std::cout << std::endl;

	std::cout << "Vector length:" << vector.getLength() << std::endl;

	Vector unitVector = vector.getUnitVector();

	std::cout << "Unit vector components: ";
	unitVector.print(std::cout);
	std::cout << std::endl;

	std::cout << "Unit vector length:" << unitVector.getLength() << std::endl << std::endl;
}

int main()
{
	double* v1components = new double[2] {6, 8};
	Vector v1(v1components, 2);

	double* v2comp = new double[5] {5, 6, 9, 8, 3};
	Vector v2(v2comp, 5);

	double* v3comp = new double[5] {-2, 6, 0, -8, 3};
	Vector v3(v3comp, 5);

	VectorOperationLogger logger("vectors.txt");

	VectorOperations operations(&logger);

	double scalar = 5;

	auto res = operations.addVectors(v3, v2);
	auto res2 = operations.subtractVectors(v3, v2);
	auto res3 = operations.areColinear(v3, v2);
	auto res4 = operations.getScalarProduct(v3, v2, scalar);
	operations.multiplyVectorByScalar(v1, 5);
}


