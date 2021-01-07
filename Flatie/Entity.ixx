#include <vector>
#include <memory>
#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>


export module Entity;


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
		 sf::Shape* s = shapes[0].get();

		 return s;
	 }

	 bool collides(Entity other) {
		 if (!boundsCollide(other)) return false;
		
		 //return checkCollision(getFirstShape(), other.getFirstShape());
	 }
};