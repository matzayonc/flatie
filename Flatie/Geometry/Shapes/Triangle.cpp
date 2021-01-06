#include "Triangle.hpp"
#include "Point.hpp"

using namespace gm;

Triangle::Triangle(Point a, Point b, Point c) {
	vertices.push_back(a);
	vertices.push_back(b);
	vertices.push_back(c);
}

Triangle::Triangle(std::array<Point, 3> points) {
	for (auto point : points)
		vertices.push_back(point);
}

bool Triangle::contains(Point point) const {
	float sAB = point.sideOfLine(vertices[0], vertices[1]);
	float sBC = point.sideOfLine(vertices[1], vertices[2]);
	float sCA = point.sideOfLine(vertices[2], vertices[0]);

	bool hasNegative = (sAB < 0) || (sBC < 0) || (sCA < 0);
	bool hasPositive = (sAB > 0) || (sBC > 0) || (sCA > 0);

	return !(hasNegative && hasPositive);
}
