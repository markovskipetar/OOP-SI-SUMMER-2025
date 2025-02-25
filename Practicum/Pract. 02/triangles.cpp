#include <iostream>
#include <fstream>

namespace CONSTANTS
{
	constexpr int TRIANGLE_POINTS_COUNT = 3;
}

struct Point
{
	double x;
	double y;
};

Point readPoint()
{
	double x, y;
	std::cin >> x >> y;
	return Point{ x, y };
}

Point readPointFromFile(std::ifstream& inFile)
{
	Point point;

	inFile.ignore();
	inFile >> point.x;

	inFile.ignore();
	inFile >> point.y;

	inFile.ignore();
	inFile.ignore();

	return point;
}

void printPoint(const Point& p)
{
	std::cout << '(' << p.x << ',' << p.y << ')' << std::endl;
}

double distance(const Point& lhs, const Point& rhs)
{
	return sqrt((lhs.x - rhs.x) * (lhs.x - rhs.x)
		+ (lhs.y - rhs.y) * (lhs.y - rhs.y));
}

double distanceToCenter(const Point& p)
{
	Point center{ 0, 0 };
	return distance(p, center);
}

struct Triangle
{
	Point A;
	Point B;
	Point C;
};

Triangle readTriangle()
{
	Point A = readPoint();
	Point B = readPoint();
	Point C = readPoint();

	return Triangle{ A, B, C };
}

Triangle readTriangleFromFile(std::ifstream& inFile)
{
	Point A = readPointFromFile(inFile);
	Point B = readPointFromFile(inFile);
	Point C = readPointFromFile(inFile);

	return Triangle{ A, B, C };
}

size_t getSizeOfTriangles(size_t pointsSize)
{
	return pointsSize / CONSTANTS::TRIANGLE_POINTS_COUNT;
}

void readTringleArrayFromFile(std::ifstream& inFile, Triangle*& trianglesArr, size_t& trianglesSize)
{
	size_t pointsSize = 0;
	inFile >> pointsSize;
	inFile.ignore();

	trianglesSize = getSizeOfTriangles(pointsSize);
	trianglesArr = new Triangle[trianglesSize];

	for (int i = 0; i < trianglesSize; i++)
	{
		trianglesArr[i] = readTriangleFromFile(inFile);
	}

	inFile.close();
}

void readTringleArrayFromFile(const char* fileName, Triangle*& triangleArr, size_t& trianglesSize)
{

	if (!fileName)
	{
		return;
	}

	std::ifstream inFile(fileName);
	if (!inFile.is_open())
	{
		return;
	}

	readTringleArrayFromFile(inFile, triangleArr, trianglesSize);
}

void savePointsToFile(std::ofstream& outFile, const Point* points, size_t pointsSize)
{
	outFile << pointsSize << std::endl;

	for (int i = 0; i < pointsSize; i++)
	{
		outFile << '(' << points[i].x << ',' << points[i].y << ')' << std::endl;
	}

	outFile.close();
}

void savePointsToFile(const char* fileName, const Point* points, size_t pointsSize)
{
	if (!fileName)
	{
		return;
	}

	std::ofstream outFile(fileName);
	if (!outFile.is_open())
	{
		return;
	}

	savePointsToFile(outFile, points, pointsSize);
}

void printTriangle(const Triangle& triangle)
{
	printPoint(triangle.A);
	printPoint(triangle.B);
	printPoint(triangle.C);
}

void printTriangles(const Triangle* trianglesArr, size_t trianglesSize)
{
	for (int i = 0; i < trianglesSize; i++)
	{
		std::cout << "Triangle: " << i << std::endl;
		printTriangle(trianglesArr[i]);
		std::cout << "---------------" << std::endl;
	}
}

double trianglePer(double a, double b, double c)
{
	return a + b + c;
}

double triangleArea(const Triangle& triangle)
{
	double a = distance(triangle.B, triangle.C);
	double b = distance(triangle.C, triangle.A);
	double c = distance(triangle.A, triangle.B);

	double halfPer = trianglePer(a, b, c) / 2;

	return sqrt(halfPer * (halfPer - a) * (halfPer - b) * (halfPer - c));
}

void getTypeOfTriangle(const Triangle& triangle)
{
	double a = distance(triangle.B, triangle.C);
	double b = distance(triangle.C, triangle.A);
	double c = distance(triangle.A, triangle.B);

	if (a == b && b == c)
	{
		std::cout << "equilateral" << std::endl;
	}

	else if (a != b && b != c)
	{
		std::cout << "sided" << std::endl;
	}

	else
	{
		std::cout << "isosceles" << std::endl;
	}
}

void sortTriangles(Triangle* triangles, int n)
{
	double* areas = new double[n];
	for (int i = 0; i < n; i++)
	{
		areas[i] = triangleArea(triangles[i]);
	}

	for (int i = 0; i < n - 1; i++)
	{
		int minArea = i;

		for (int j = i + 1; j < n; j++)
		{
			if (areas[j] < areas[minArea])
			{
				minArea = j;
			}
		}

		if (minArea != i)
		{
			std::swap(triangles[i], triangles[minArea]);
			std::swap(areas[i], areas[minArea]);
		}
	}

	delete[] areas;
}

void freeTrianglesArr(Triangle*& trianglesArr, size_t& trianglesSize)
{
	delete[] trianglesArr;
	trianglesArr = nullptr;

	trianglesSize = 0;
}

int main()
{
	size_t pointsSize;
	std::cin >> pointsSize;

	Point* points = new Point[pointsSize];
	for (int i = 0; i < pointsSize; i++)
	{
		std::cin >> points[i].x >> points[i].y;
	}

	savePointsToFile("points.txt", points, pointsSize);

	Triangle* trianglesArr = nullptr;
	size_t trianglesSize = 0;
	readTringleArrayFromFile("points.txt", trianglesArr, trianglesSize);

	printTriangles(trianglesArr, trianglesSize);
	freeTrianglesArr(trianglesArr, trianglesSize);

	return 0;
}