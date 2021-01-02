#include <vector>
#include <memory>
#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>


export module Abstract;


export class Entity {
protected:
	std::vector<sf::RectangleShape> shapes;
	std::vector<sf::CircleShape> circles;
	sf::Clock tick;


	virtual void update() {
		tick.restart();
	}

	virtual void clearShapes() {
		shapes.clear();
		circles.clear();
	}

	virtual void resetShapes() {}


public:
	 void render(sf::RenderWindow& window){
		update();

		for (auto i : shapes)
			window.draw(i);

		for(auto i : circles)
			window.draw(i);
	 }
};