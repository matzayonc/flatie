#pragma once
#include <vector>
#include <array>
#include <limits>
#include "Point.hpp"

namespace gm {
	class Triangle;

	class Shape{
	protected:
		bool trianglified = false;
		Vector offset{0, 0};

		std::vector<Point> vertices;
		std::vector<Triangle> triangles;
		Point highiestPoint{0, 0};
		Point lowestPoint{0, 0};
		float rotation;

		void trianglify();
		void setRotationRad(float radians);

	public:
		Shape& operator+=(const Vector& other);
		Point operator[](size_t index) const;

		size_t getVerticesCount() const;
		double getArea() const;
		bool contains(Point& point);
		bool collides(Shape* shape);
		bool crosses(Shape* shape);

		void move(const Vector& vector);

		Point getHighiest() const;
		Point getLowest() const;
		Vector getOffset() const;
		bool boundsCollide(Shape* shape) const;

		float getRotation();
		void setRotation(float angle);
		void rotate(float angle);


		template<class T>
		Shape(T points) { ///IDK how to move id to cpp :(
			if (!points.size()) throw "Too short";
			
			for (auto point : points)
				vertices.push_back(point);


			offset = Point(0, 0) - vertices[0];

			highiestPoint = vertices[0];
			lowestPoint = vertices[0];

			for (auto point : points) {
				if (point.x > highiestPoint.x)
					highiestPoint.x = point.x;
				if (point.y > highiestPoint.y)
					highiestPoint.y = point.y;

				if (point.x < lowestPoint.x)
					lowestPoint.x = point.x;
				if (point.y < lowestPoint.y)
					lowestPoint.y = point.y;
			}

		}
	};
}
