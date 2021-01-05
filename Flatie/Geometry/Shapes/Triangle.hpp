#pragma once
#include "Triangle.hpp"
#include "Shape.hpp"

namespace gm {
	class Triangle :public Shape {
	public:
		Triangle(Point a, Point b, Point c);
		
		bool contains(Point point) const;
	};

}

