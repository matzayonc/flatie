#pragma once

namespace gm {

	class Point {
	protected:

	public:
		double x;
		double y;
		Point(double x, double y);
		Point(Point &point);
	};

}