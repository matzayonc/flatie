#include <vector>
#include <memory>
#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>


export module Abstract;


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
	 void render(sf::RenderWindow& window){
		update();

		for (auto& i : shapes)
			window.draw(*i.get());
	 }
};