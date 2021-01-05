#pragma once
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
	};

}