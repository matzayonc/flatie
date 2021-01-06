#pragma once
#include <array>
#include <iostream>
#include "Triangle.hpp"
#include "Shape.hpp"

namespace gm {
	class Triangle :public Shape {
	public:
		Triangle(Point a, Point b, Point c);
		Triangle(std::array<Point, 3> points);
		
		bool contains(Point point) const;
		bool collides(Shape shape) const;

	private:
		void trianglify(){
			std::cout << "a";
		};
	};

}

