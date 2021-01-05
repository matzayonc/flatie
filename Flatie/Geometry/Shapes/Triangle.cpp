#include "Triangle.hpp"
#include "Point.hpp"

using namespace gm;

Triangle::Triangle(Point a, Point b, Point c) {
	vertices.push_back(a);
	vertices.push_back(b);
	vertices.push_back(c);
}
