#include <vector>
#include <memory>
#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>


export module Entity;
import Collisions;


export class Entity {
protected:
	std::vector<std::shared_ptr<sf::Shape>> shapes;
	sf::Clock clock;

	float tick() {
		float time = (float)clock.getElapsedTime().asMicroseconds() / 1e6f;
		clock.restart();
		return time;
	}

	virtual void update() {}

	virtual void resetShapes() {}



public:
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
		 return shapes[0].get();
	 }



	 bool collides(Entity other) const {
		 //return other.getGlobalBounds().intersects(shapes[0]->getGlobalBounds());
		 /*
		 sf::Shape* s = shapes[0].get();
		 sf::Vector2f a = s->getTransform().transformPoint(s->getPoint(0));
		 sf::Vector2f b = s->getTransform().transformPoint(s->getPoint(1));
		 sf::Vector2f c = s->getTransform().transformPoint(s->getPoint(2));

		 sf::Shape* o = other.getFirstShape();
		 sf::Vector2f p = o->getTransform().transformPoint(o->getPoint(0));
		 */




		 //return pointInShape(sf::Vector2f(0, 0), a);
		 //return pointInTriangle(p, a, b, c);
		 return checkCollisions(getFirstShape(), other.getFirstShape());
	 }
};