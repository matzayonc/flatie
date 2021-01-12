#pragma once
#include "Point.hpp"
#include "Vector.hpp"
#include <iostream>
#include <cmath>

using namespace gm;


Point::Point(double x, double y) : x(x), y(y) {};
Point::Point(const Point& point) : x(point.x), y(point.y) {};

double Point::distanceTo(Point point) const {
	return std::sqrt(std::pow(x, 2) + std::pow(y, 2));
}

Point Point::operator+(const Vector& vector) const {
	Point point(x + vector.x, y + vector.y);
	return point;
}

Point& Point::operator+=(const Vector& vector){
	x += vector.x;
	y += vector.y;
	return *this;
}

Vector Point::operator-(const Point& point) const {
	return Vector(point.x - x, point.y - y);
}


void Point::moveBy(const Vector& vector) {
	x += vector.x;
	y += vector.y;
}

double Point::sideOfLine(Point a, Point b) const {
	return (x - b.x) * (a.y - b.y) - (a.x - b.x) * (y - b.y);
}

bool Point::doLinesCross(Point other, Point a, Point b) const {
	double denominator = ((b.x - a.x) * (y - other.y)) - ((b.y - a.y) * (x - other.x));
	double numerator1 = ((a.y - other.y) * (x - other.x)) - ((a.x - other.x) * (y - other.y));
	double numerator2 = ((a.y - other.y) * (b.x - a.x)) - ((a.x - other.x) * (b.y - a.y));

	if (denominator == 0) return numerator1 == 0 && numerator2 == 0;

	double r = numerator1 / denominator;
	double s = numerator2 / denominator;

	return (r >= 0 && r <= 1) && (s >= 0 && s <= 1);
}

