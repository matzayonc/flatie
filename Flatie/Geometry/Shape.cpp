#include <iostream>
#include "Shape.hpp"
#include "Point.hpp"
#include "Triangle.hpp"

using namespace gm;


size_t Shape::getVerticesCount() const {
	return vertices.size();
}

Point Shape::operator[](size_t index) const {
	return vertices[index];
}

double Shape::getArea() const {
	double area = 0;
	size_t j = vertices.size() - 1;
	for (int i = 0; i < vertices.size(); i++) {
		area += (vertices[j].x + vertices[i].x) * (vertices[j].y - vertices[i].y);
		j = i;
	}
	area /= 2;

	return area > 0 ? area : -area;
}

bool Shape::contains(Point& point) {
	if(!trianglified)
		trianglify();

	for (Triangle& triangle : triangles)
		if (triangle.contains(point))
			return true;

	return false;
}

void Shape::trianglify() {
	trianglified = true;
	size_t count = getVerticesCount();
	for (size_t i = 0; i < count; i++) 
		for (size_t j = 0; j < count; j++)
			if(i != j && i+1 != j)
				triangles.push_back(Triangle(vertices[i], vertices[(i+1)%count], vertices[j]));
}


bool Shape::collides(Shape* shape) {
	if (!trianglified)
		trianglify();

	for (Triangle& triangle : triangles)
		for (size_t i = 0; i < shape->getVerticesCount(); i++) {
			Point point = (*shape)[i];
			if (triangle.contains(point))
				return true;
		}

	return false;
}
