#pragma once

namespace gm {

	class Point {
	protected:

	public:
		double x;
		double y;
		Point(double x, double y);
		Point(Point &point);
		double distanceTo(Point point) const;
		Point operator+(Vector vector) const;
		void moveBy(Vector vector);
	};

}