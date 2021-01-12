#pragma once
#include "Vector.hpp"
#include "Point.hpp"


using namespace gm;

Vector::Vector(double x, double y)
	: x(x), y(y) {};


Vector::Vector(Point from, Point to) {
	x = to.x - from.x;
	y = to.y - from.y;
}

Vector& Vector::operator+=(const Vector& vector) {
	x += vector.x;
	y += vector.y;
	return *this;
}
