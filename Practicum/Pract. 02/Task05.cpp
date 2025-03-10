#include <iostream>
#include <fstream>

namespace Constants {
	const size_t BUFFER_SIZE = 1024;
	const size_t START_POS = 0;
}

struct Point {
	int x, y;
};

struct Triangle {
	Point a, b, c;
};

void writePointsToFile(const char* filename, const Point* points, size_t size) {
	std::ofstream ofs(filename);
	if (!ofs.is_open()) {
		std::cout << "File not found" << std::endl;
		return;
	}
	for (size_t i = 0; i < size; i++) {
		ofs << points[i].x << ' ' << points[i].y << '\n';
	}
	ofs.close();
}

size_t getPointsCount(std::ifstream& ifs) {
	if (!ifs.is_open()) {
		std::cout << "File not found" << std::endl;
		return -1;
	}

	size_t count = 0;

	while (true) {
		if (ifs.eof()) {
			break;
		}

		char buffer[Constants::BUFFER_SIZE];
		ifs.getline(buffer, Constants::BUFFER_SIZE);

		count++;
	}

	ifs.clear();
	ifs.seekg(Constants::START_POS, std::ios::beg);

	return count - 1; //subtracting 1 because the last line is empty because of line 24
}

bool checkIfTriangleExists(Triangle triangle) {
	float side1 = sqrt((triangle.a.x - triangle.b.x) * (triangle.a.x - triangle.b.x) +
		(triangle.a.y - triangle.b.y) * (triangle.a.y - triangle.b.y));
	float side2 = sqrt((triangle.b.x - triangle.c.x) * (triangle.b.x - triangle.c.x) +
		(triangle.b.y - triangle.c.y) * (triangle.b.y - triangle.c.y));
	float side3 = sqrt((triangle.a.x - triangle.c.x) * (triangle.a.x - triangle.c.x) +
		(triangle.a.y - triangle.c.y) * (triangle.a.y - triangle.c.y));

	return (side1 + side2 > side3) && (side1 + side3 > side2) && (side2 + side3 > side1);
}

Triangle* readPointsFromFileAsTriangles(const char* filename, size_t& size) {
	std::ifstream ifs(filename);
	if (!ifs.is_open()) {
		std::cout << "File not found" << std::endl;
		return nullptr;
	}

	size_t pointCount = getPointsCount(ifs);

	if (pointCount == -1) {
		ifs.close();
		return nullptr;
	}

	size = pointCount / 3;

	Triangle* triangles = new Triangle[size];

	for (size_t i = 0; i < size; i++) {
		Triangle triangle;
		ifs >> triangle.a.x >> triangle.a.y;
		ifs >> std::ws;
		ifs >> triangle.b.x >> triangle.b.y;
		ifs >> std::ws;
		ifs >> triangle.c.x >> triangle.c.y;
		ifs >> std::ws;
		if (checkIfTriangleExists(triangle)) {
			triangles[i] = triangle;
		}
		else {
			std::cout << "Invalid triangle" << std::endl;
		}
	}

	ifs.close();

	return triangles;
}

void printTriangles(Triangle* triangles, size_t size) {
	for (size_t i = 0; i < size; i++) {
		std::cout << "Triangle " << i + 1 << ": (" << triangles[i].a.x << ", " << triangles[i].a.y << "), ("
			<< triangles[i].b.x << ", " << triangles[i].b.y << "), ("
			<< triangles[i].c.x << ", " << triangles[i].c.y << ")" << std::endl;
	}
}

int main() {
	size_t size = 0;
	std::cin >> size;

	Point* points = new Point[size];
	for (size_t i = 0; i < size; i++) {
		std::cin >> points[i].x >> points[i].y;
	}

	writePointsToFile("points.txt", points, size);

	delete[] points;

	Triangle* triangles = readPointsFromFileAsTriangles("points.txt", size);
	if (triangles == nullptr) {
		std::cout << "No triangles found" << std::endl;
		return 0;
	}

	printTriangles(triangles, size);

	delete[] triangles;
}