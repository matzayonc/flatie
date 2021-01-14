#include <iostream>
#include "Shape.hpp"
#include "Point.hpp"
#include "Triangle.hpp"
#include <chrono>

using namespace gm;


size_t Shape::getVerticesCount() const {
	return vertices.size();
}

Point Shape::operator[](size_t index) const {
	return vertices[index];
}

Shape& Shape::operator+=(const Vector& vector) {
	move(vector);
	return *this;
}

void Shape::move(const Vector& vector) {
	for (auto& verticle : vertices)
		verticle.moveBy(vector);

	offset += vector;
	lowestPoint.moveBy(vector);
	highiestPoint.moveBy(vector);

	if (trianglified)
		for (auto& triangle : triangles)
			triangle.move(vector);
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

Vector Shape::getOffset() const {
	return offset;
}


bool Shape::contains(Point& point) {
	if (!(lowestPoint.x <= point.x && point.x <= highiestPoint.x)) return false;
	if (!(lowestPoint.y <= point.y && point.y <= highiestPoint.y)) return false;

	if(!trianglified)
		trianglify();

	for (Triangle& triangle : triangles)
		if (triangle.contains(point))
			return true;

	return false;
}


void Shape::trianglify() {
	size_t count = getVerticesCount();
	for (size_t i = 0; i < count; i++) 
		for (size_t j = 0; j < count; j++)
			if(i != j && i+1 != j)
				triangles.push_back(Triangle(vertices[i], vertices[(i+1)%count], vertices[j]));
	
	trianglified = true;
}

bool Shape::collides(Shape* shape) {
	if (!boundsCollide(shape)) return false;
	if (crosses(shape)) return true;

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

bool Shape::crosses(Shape* shape) {
	for (size_t i = 0; i < getVerticesCount(); i++)
		for (size_t j = 0; j < shape->getVerticesCount(); j++)
			if (vertices[i].doLinesCross(
				vertices[(i + 1) % getVerticesCount()],
				(*shape)[j], (*shape)[(j + 1) % shape->getVerticesCount()]
			)) return true;

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

float Shape::getRotation() {
	return rotation * 180.f / 3.141592654f;
}

void Shape::setRotation(float angle) {
	setRotationRad(angle * 3.141592654f / 180.f);
}

void Shape::rotate(float angle) {
	setRotationRad(rotation + angle * 3.141592654f / 180.f);
}

void Shape::setRotationRad(float radians) {
	//WRITE ME!
}
