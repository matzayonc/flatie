#pragma once
#include "Point.hpp"
#include "Vector.hpp"
#include <cmath>

using namespace gm;


Point::Point(double x, double y) : x(x), y(y) {};
Point::Point(const Point& point) : x(point.x), y(point.y) {};

double Point::distanceTo(Point point) const {
	if (!x && !y) return 0;
	return std::sqrt(std::pow(x, 2) + std::pow(y, 2));
}

Point Point::operator+(Vector vector) const {
	Point point(x + vector.x, y + vector.x);
	return point;
}

void Point::moveBy(Vector vector) {
	x += vector.x;
	y += vector.y;
}

double Point::sideOfLine(Point a, Point b) const {
	return (x - b.x) * (a.y - b.y) - (a.x - b.x) * (y - b.y);
}
