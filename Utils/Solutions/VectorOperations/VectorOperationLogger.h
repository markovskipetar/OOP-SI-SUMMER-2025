#pragma once
#include "Vector.h"


class VectorOperationLogger
{
public:
	VectorOperationLogger(const char* logFileName);

	void logAddition(const Vector& lhs, const Vector& rhs);
	void logSubtraction(const Vector& lhs, const Vector& rhs);
	void logMultiplycationByScalar(Vector& vector, double scalar);
	void logScalarProduct(const Vector& lhs, const Vector& rhs);
	void logUnitVector(const Vector& vector);
	void logAreColinear(const Vector& lhs, const Vector& rhs);

private:
	std::ofstream logger;
};

