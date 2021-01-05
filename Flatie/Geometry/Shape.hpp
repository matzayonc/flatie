#pragma once
#include <vector>
#include "Point.hpp"

namespace gm {
	class Shape{
	public:
		size_t getVerticesCount();
		Point operator[](size_t index);

	protected:
		std::vector<Point> vertices;
	};
}
