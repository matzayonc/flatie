#pragma once
#include <vector>
#include <array>
#include "Point.hpp"

namespace gm {
	class Triangle;

	class Shape{
	public:
		template<class T>
		Shape(T points) { ///IDK how to move id to cpp :(
			for (auto point : points)
				vertices.push_back(point);
		}

		size_t getVerticesCount() const;
		Point operator[](size_t index) const;
		double getArea() const;
		bool contains(const Point& point);
		bool collides(const Shape& shape);

	protected:
		bool trianglified = false;

		void trianglify();
		std::vector<Point> vertices;
		std::vector<Triangle> triangles;
	};
}
