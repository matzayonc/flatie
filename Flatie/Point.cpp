#pragma once
#include "Point.hpp"

using namespace gm;

Point::Point(double x, double y) : x(x), y(y) {};
Point::Point(Point& point) : x(point.x), y(point.x) {};