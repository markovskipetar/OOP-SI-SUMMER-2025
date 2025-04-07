#include "VectorOperations.h"

VectorOperations::VectorOperations(VectorOperationLogger* logger)
	: logger(logger)
{

}

OperationResult VectorOperations::addVectors(const Vector& lhs, const Vector& rhs) const
{
	int lhsSize = lhs.getSize();
	int rhsSize = rhs.getSize();

	if (lhsSize != rhsSize)
	{
		return OperationResult(false);
	}

	const double* lhsComponents = lhs.getComponents();
	const double* rhsComponents = rhs.getComponents();

	double* resultVectorComponents = new double[lhsSize];

	for (int i = 0; i < lhsSize; i++)
	{
		resultVectorComponents[i] = (lhsComponents[i] + rhsComponents[i]);
	}

	OperationResult operationResult(true, resultVectorComponents, lhsSize);

	delete[] resultVectorComponents;

	logger->logAddition(lhs, rhs);

	return operationResult;
}

OperationResult VectorOperations::subtractVectors(const Vector& lhs, const Vector& rhs) const
{
	if (lhs.getSize() != rhs.getSize())
	{
		return OperationResult(false);
	}

	const double* lhsComponents = lhs.getComponents();
	const double* rhsComponents = rhs.getComponents();

	double* resultVectorComponents = new double[lhs.getSize()];

	for (int i = 0; i < lhs.getSize(); i++)
	{
		resultVectorComponents[i] = (lhsComponents[i] - rhsComponents[i]);
	}

	OperationResult operationResult(true, resultVectorComponents, lhs.getSize());

	delete[] resultVectorComponents;

	logger->logSubtraction(lhs, rhs);

	return operationResult;
}

void VectorOperations::multiplyVectorByScalar(Vector& vector, double scalar) const
{
	logger->logMultiplycationByScalar(vector, scalar);

	vector.multiplyByScalar(scalar);
}

bool VectorOperations::getScalarProduct(const Vector& lhs, const Vector& rhs, double& scalarProduct) const
{
	if (lhs.getSize() != rhs.getSize())
	{
		return false;
	}

	const double* lhsComponents = lhs.getComponents();
	const double* rhsComponents = rhs.getComponents();

	scalarProduct = 0;

	for (int i = 0; i < lhs.getSize(); i++)
	{
		scalarProduct += (lhsComponents[i] * rhsComponents[i]);
	}

	logger->logScalarProduct(lhs, rhs);

	return true;
}

Vector VectorOperations::getUnitVector(const Vector& vector) const
{
	logger->logUnitVector(vector);

	return vector.getUnitVector();
}

bool VectorOperations::areColinear(const Vector& lhs, const Vector& rhs) const
{
	if (lhs.getSize() != rhs.getSize())
	{
		return false;
	}

	logger->logAreColinear(lhs, rhs);

	const double* lhsComponents = lhs.getComponents();
	const double* rhsComponents = rhs.getComponents();

	double ratio = (lhsComponents[0] / rhsComponents[0]);

	for (int i = 1; i < lhs.getSize(); i++)
	{
		if (!lhsComponents[i] && !rhsComponents[i])
		{
			continue;
		}

		if (!lhsComponents[i] || !rhsComponents[i])
		{
			return false;
		}

		double currentRatio = (lhsComponents[i] / rhsComponents[i]);

		if (currentRatio != ratio)
		{
			return false;
		}
	}

	return true;
}