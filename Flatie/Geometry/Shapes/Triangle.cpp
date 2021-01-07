#include <array>
#include "Triangle.hpp"
#include "Point.hpp"
#include "Shape.hpp"

using namespace gm;
Triangle::Triangle(Point a, Point b, Point c):
	Shape(std::array<Point, 3>{ a, b, c }) {}


Triangle::Triangle(std::array<Point, 3> points):Shape(points) {}

bool Triangle::contains(Point point) const {
	float sAB = point.sideOfLine(vertices[0], vertices[1]);
	float sBC = point.sideOfLine(vertices[1], vertices[2]);
	float sCA = point.sideOfLine(vertices[2], vertices[0]);

	bool hasNegative = (sAB < 0) || (sBC < 0) || (sCA < 0);
	bool hasPositive = (sAB > 0) || (sBC > 0) || (sCA > 0);

	return !(hasNegative && hasPositive);
}


bool Triangle::collides(Shape shape) const {

	for (size_t i = 0; i < shape.getVerticesCount(); i++)
		if (contains(shape[i]))
			return true;

	return false;
}
