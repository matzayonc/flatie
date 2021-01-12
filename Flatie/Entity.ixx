
#include <vector>
#include <memory>
#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include "Geometry/Shape.hpp"
#include "Geometry/Shapes/Triangle.hpp"
#include "Geometry/Point.hpp"


export module Entity;

export class Entity {
protected:
	sf::Clock clock;
	std::vector<std::shared_ptr<sf::Shape>> shapes;
	//gm::Shape* hitbox;
	std::unique_ptr<gm::Shape> hitbox;

	float tick() {
		float time = (float)clock.getElapsedTime().asMicroseconds() / 1e6f;
		clock.restart();
		return time;
	}

	virtual void update() {}

	virtual void resetShapes() {}

	void hitboxFromShapes() {
		if (!shapes.size()) throw "no shapes in Entity";
		std::vector<gm::Point> points;

		for (int i = 0; i < shapes[0]->getPointCount(); i++) {
			sf::Vector2f vector = shapes[0]->getTransform().transformPoint(shapes[0]->getPoint(i));
			points.push_back(gm::Point(vector.x, vector.y));
		}

		hitbox = std::make_unique<gm::Shape>(points);
	}

public:
	Entity() {
	}

	Entity(const Entity&) = delete;

	Entity& operator+=(const gm::Vector& vector) {
		move(vector);
		return *this;
	}

	void move(const gm::Vector& vector) {
		if (!vector.x && !vector.y) return;

		hitbox->move(vector);

		for (auto& shape : shapes)
			shape->setPosition(sf::Vector2f(hitbox->getOffset().x, hitbox->getOffset().y));
			//shape->setPosition(shape->getPosition() + sf::Vector2f((float)vector.x, (float)vector.y));
	}

	void move(double x, double y) {
		move(gm::Vector(x, y));
	}

	gm::Shape* getHitbox() const {
		return hitbox.get();
	}

	sf::Vector2f getCoords() {
		if (!shapes.size()) sf::Vector2f{ 0.f, 0.f };
			
		return shapes[0]->getPosition();
	}

	sf::FloatRect getGlobalBounds() {
		if (!shapes.size()) sf::FloatRect{ 0.f, 0.f, 0.f, 0.f };

		return shapes[0]->getGlobalBounds();
	}

	 void render(sf::RenderWindow& window){
		update();

		for (auto& i : shapes)
			window.draw(*i.get());
	 }

	 bool boundsCollide(Entity other) const {
		 return other.getGlobalBounds().intersects(shapes[0]->getGlobalBounds());
	 }

	 sf::Shape* getFirstShape() {
		 sf::Shape* s = shapes[0].get();

		 return s;
	 }

	 bool collides(const Entity& other) {
		 //if (!boundsCollide(other)) return false;

		 if (hitbox->collides(other.getHitbox())) return true;

		 if (other.getHitbox()->collides(getHitbox())) return true;

		 return false;
		
	 }
};