#include "VectorOperationLogger.h"

VectorOperationLogger::VectorOperationLogger(const char* logFileName)
{
	logger.open(logFileName, std::ios::app);
}

void VectorOperationLogger::logAddition(const Vector& lhs, const Vector& rhs) 
{
	lhs.print(logger);
	logger << " + ";
	rhs.print(logger);
	logger << std::endl;
}

void VectorOperationLogger::logSubtraction(const Vector& lhs, const Vector& rhs) 
{
	lhs.print(logger);
	logger << " - ";
	rhs.print(logger);
	logger << std::endl;
}

void VectorOperationLogger::logMultiplycationByScalar(Vector& vector, double scalar) 
{
	logger << scalar << " * ";
	vector.print(logger);
	logger << std::endl;
}

void VectorOperationLogger::logScalarProduct(const Vector& lhs, const Vector& rhs) 
{
	lhs.print(logger);
	logger << " * ";
	rhs.print(logger);
	logger << std::endl;
}

void VectorOperationLogger::logUnitVector(const Vector& vector) 
{
	logger << "Unit vector of: ";
	vector.print(logger);
	logger << std::endl;
}

void VectorOperationLogger::logAreColinear(const Vector& lhs, const Vector& rhs) 
{
	lhs.print(logger);
	logger << " || ";
	rhs.print(logger);
	logger << std::endl;
}