#include "Shape.hpp"
#include "Point.hpp"

using namespace gm;

size_t Shape::getVerticesCount() {
	return vertices.size();
}

Point Shape::operator[](size_t index) {
	return vertices[index];
}