#pragma once
#include <iostream>
#include "Vector.hpp"

namespace gm {
	class Point {
	protected:

	public:
		double x;
		double y;
		Point(double x, double y);
		Point(const Point &point);
		double distanceTo(Point point) const;

		Point operator+(Vector vector) const;

		void moveBy(Vector vector);
		double sideOfLine(Point a, Point b) const;

		friend std::ostream& operator<<(std::ostream& output, const Point& point) {
			return output << '(' << point.x << ", " << point.y << ')';
		};
	};

}