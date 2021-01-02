#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>


export module Abstract;


export class Entity {
protected:
	std::vector<sf::RectangleShape> shapes;
	sf::Clock tick;


	virtual void update() {
		tick.restart();
	}

public:
	virtual void render(sf::RenderWindow& window) {
		update();

		for (const auto i : shapes)
			window.draw(i);
	}
};