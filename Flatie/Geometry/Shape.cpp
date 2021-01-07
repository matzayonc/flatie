#include "Shape.hpp"
#include "Point.hpp"

using namespace gm;


size_t Shape::getVerticesCount() const {
	return vertices.size();
}

Point Shape::operator[](size_t index) const {
	return vertices[index];
}

double Shape::getArea() const {
	double area = 0;
	int j = vertices.size() - 1;
	for (int i = 0; i < vertices.size(); i++) {
		area += (vertices[j].x + vertices[i].x) * (vertices[j].y - vertices[i].y);
		j = i;
	}
	area /= 2;

	return area > 0 ? area : -area;
}

bool Shape::contains(Point point) const {
	/*
	
	sf::Vector2f first = trasformedPoint(shape, 0);
	sf::Vector2f second = trasformedPoint(shape, shape->getPointCount() - 1);

	for (int j = 1; j < shape->getPointCount() - 1; j++)
		if (pointInTriangle(point, first, second, trasformedPoint(shape, j)))
			return true;

	for (int i = 1; i < shape->getPointCount(); i++) {
		first = trasformedPoint(shape, i - 1);
		second = trasformedPoint(shape, i);

		for (int j = i; j < shape->getPointCount(); j++)
			if (pointInTriangle(point, first, second, trasformedPoint(shape, j)))
				return true;
	}

	return false;*/
	return false;
}
