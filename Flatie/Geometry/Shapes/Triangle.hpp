#pragma once
#include <array>
#include "Triangle.hpp"
#include "Shape.hpp"

namespace gm {
	class Triangle :public Shape {
	public:
		Triangle(Point a, Point b, Point c);
		Triangle(std::array<Point, 3> points);
		
		bool contains(Point point) const;
	};

}

