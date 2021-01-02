#include <vector>
#include <memory>
#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>


export module Abstract;


export class Entity {
protected:
	std::vector<std::shared_ptr<sf::Shape>> shapes;
	sf::Clock tick;


	virtual void update() {
		tick.restart();
	}

	virtual void resetShapes() {}


public:
	 void render(sf::RenderWindow& window){
		update();

		for (auto& i : shapes)
			window.draw(*i.get());
	 }
};