#pragma once
#include <vector>
#include <array>
#include "Point.hpp"

namespace gm {
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
		bool contains(Point point) const;

	protected:
		std::vector<Point> vertices;
	};
}
