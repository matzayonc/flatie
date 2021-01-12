#pragma once
namespace gm {
	class Vector;
};

#include "Point.hpp"


namespace gm {
	class Vector {
	public:
		double x, y;
		Vector(double x, double y);
		Vector(Point from, Point to);
		Vector& operator+=(const Vector& vector);
	};

};