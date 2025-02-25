#include <iostream>
const double EPS = 1e-9;

struct Point {
	int x;
	int y;

	void readPoint() {
		std::cin >> x >> y;
	}

	void printPoint() const {
		std::cout << "(" << x << ", " << y << ")";
	}

	double getDistanceToCenter() const {
		return sqrt(x * x + y * y);
	}
};

double getDistanceBetweenPoints(const Point& pointOne, const Point& pointTwo) {
	int distanceX = pointOne.x - pointTwo.x;
	int distanceY = pointOne.y - pointTwo.y;

	return sqrt(distanceX * distanceX + distanceY * distanceY);
}


enum  TriangleType {
	Equilateral,
	Isosceles,
	Scalene
};

struct Triangle {
	Point A, B, C;

	void readTriangle() {
		A.readPoint();
		B.readPoint();
		C.readPoint();
	}

	void printTriangle() const {
		std::cout << "A="; A.printPoint();
		std::cout << ", B="; B.printPoint();
		std::cout << ", C="; C.printPoint();
	}

	double sideAB() const { return getDistanceBetweenPoints(A, B); }
	double sideBC() const { return getDistanceBetweenPoints(B, C); }
	double sideCA() const { return getDistanceBetweenPoints(C, A); }

	double getPerimeter() const {
		return sideAB() + sideBC() + sideCA();
	}

	double getArea() const {
		double sideA = sideBC();
		double sideB = sideCA();
		double sideC = sideAB();

		double s = (sideA + sideB + sideC) * 0.5;

		return sqrt(s * (s - sideA) * (s - sideB) * (s - sideC));
	}

	TriangleType getTriangleType() {
		double sideA = sideBC();
		double sideB = sideCA();
		double sideC = sideAB();

		bool abEqual = (std::abs(sideA - sideB) < EPS);
		bool bcEqual = (std::abs(sideB - sideC) < EPS);
		bool acEqual = (std::abs(sideA - sideC) < EPS);

		if (abEqual && bcEqual && acEqual) {
			return Equilateral;
		}
		else if (abEqual || bcEqual || acEqual) {
			return Isosceles;
		}
		else {
			return Scalene;
		}
	}
};

const char* toString(TriangleType type) {
	switch (type) {
		case Equilateral: return "Equilateral";
		case Isosceles: return "Isosceles";
		case Scalene: return "Scalene";
	}
}

void readAndSortTriangleArray() {
	int N;
	std::cout << "N =";
	std::cin >> N;

	Triangle* triangles = new Triangle[N];

	for (int i = 0; i < N; i++) {
		std::cout << "Enter the coordinates of triangle #" << (i + 1)
			<< " (xA yA xB yB xC yC): ";
		triangles[i].readTriangle();
	}

	for (int i = 1; i < N; i++) {
		Triangle key = triangles[i];
		double keyArea = key.getArea();

		int j = i - 1;

		while (j >= 0 && keyArea < triangles[j].getArea()) {
			triangles[j + 1] = triangles[j];
			j--;
		}

		triangles[j + 1] = key;
	}

	for (int i = 0; i < N; i++) {
		std::cout << "Triangle #" << (i + 1) << ": ";

		triangles[i].printTriangle();
		std::cout << "\n  Type: " << toString(triangles[i].getTriangleType())
			<< "\n  Area: " << triangles[i].getArea()
			<< "\n  Perimeter: " << triangles[i].getPerimeter()
			<< "\n";
	}

	delete[] triangles;
}

int main()
{

}

