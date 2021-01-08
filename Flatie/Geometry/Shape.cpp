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
	if (!(lowestPoint.x <= point.x <= highiestPoint.x)) return false;
	if (!(lowestPoint.y <= point.y <= highiestPoint.y)) return false;

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
	if (!boundsCollide(shape)) return false;

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


bool Shape::boundsCollide(Shape* shape) const {
	if (getLowest().x > shape->getHighiest().x) return false;
	if (getHighiest().x < shape->getLowest().x) return false;
	if (getLowest().y > shape->getHighiest().y) return false;
	if (getHighiest().y < shape->getLowest().y) return false;
	return true;
}


Point Shape::getHighiest() const {
	return highiestPoint;
}

Point Shape::getLowest() const {
	return lowestPoint;
}