#include <vector>
#include <SFML/Graphics.hpp>

export module Person;
import Abstract;

export class Person : public Entity {
private:

	void resetShapes() {

		auto head = std::make_shared<sf::CircleShape>(.5f, 30);
		head->setOrigin(3, 3);
		head->setFillColor(sf::Color::Red);

		shapes.push_back(head);
	}

public:
	Person() {
		resetShapes();
	}
};