#pragma once
#include <iostream>

namespace gm {
	class Point;
}

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

		Point operator+(const Vector& vector) const;
		Point& operator+=(const Vector& vector);
		Vector operator-(const Point& point) const;

		void moveBy(const Vector& vector);
		double sideOfLine(Point a, Point b) const;
		bool doLinesCross(Point other, Point a, Point b) const;

		friend std::ostream& operator<<(std::ostream& output, const Point& point) {
			return output << '(' << point.x << ", " << point.y << ')' << std::endl;
		};
	};

}