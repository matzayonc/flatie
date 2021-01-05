#pragma once
#include <vector>
#include "Point.hpp"

namespace gm {
	class Shape{
	public:
		size_t getVerticesCount() const;
		Point operator[](size_t index) const;
		double getArea() const;
		bool contains(Point point) const;

	protected:
		std::vector<Point> vertices;
	};
}
