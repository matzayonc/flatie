#include <vector>
#include <SFML/Graphics.hpp>

export module Person;
import Abstract;

export class Person : public Entity {
private:

	void resetShapes() {

		sf::CircleShape head(.5f, 30);
		head.setPosition(3, 3);
		head.setOrigin(3, 3);
		head.setFillColor(sf::Color::Red);

		circles.push_back(head);
	}

public:
	Person() {
		resetShapes();
	}
};