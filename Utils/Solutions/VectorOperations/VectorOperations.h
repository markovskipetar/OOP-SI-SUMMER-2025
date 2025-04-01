#pragma once
#include "Vector.h"
#include "VectorOperationLogger.h"

struct OperationResult
{
	OperationResult(bool isSuccessfull, const double* components = nullptr, int size = -1)
		: isSuccessfull(isSuccessfull), vector(components, size)
	{

	}

	bool isSuccessfull;
	Vector vector;
};

class VectorOperations
{
public:
	VectorOperations(VectorOperationLogger* logger);

	OperationResult addVectors(const Vector& lhs, const Vector& rhs) const;
	OperationResult subtractVectors(const Vector& lhs, const Vector& rhs) const;
	void multiplyVectorByScalar(Vector& vector, double scalar) const;
	bool getScalarProduct(const Vector& lhs, const Vector& rhs, double& scalarProduct) const;
	Vector getUnitVector(const Vector& vector) const;
	bool areColinear(const Vector& lhs, const Vector& rhs) const;

private:
	VectorOperationLogger* logger;
};

