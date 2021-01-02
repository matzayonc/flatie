#include <vector>
#include <iostream>
#include <SFML/Graphics.hpp>

export module Person;
import Entity;

export class Person : public Entity {
private:
	sf::Vector2f direction{ 0, 0 };
	float speed = 1e-1f;

	void resetShapes() {

		auto head = std::make_shared<sf::CircleShape>(.5f, 30);
		head->setOrigin(3, 3);
		head->setFillColor(sf::Color::Red);

		shapes.push_back(head);
	}



	void update() {
		float dTime = tick();

		for (auto& i : shapes)
			i->setPosition(i->getPosition() + speed * direction);
	}

public:
	Person() {
		resetShapes();
	}

	void go(sf::Vector2f whereTo) {
		direction = whereTo;
	}

	void teleport(sf::Vector2f whereTo) {
		direction = whereTo;
		for (auto& i : shapes)
			i->setPosition(whereTo);
	}
};


export void steerAPerson(Person& person) {

	sf::Vector2f dir(.0f, .0f);
	
	auto sq = sqrt(dir.x * dir.x + dir.y * dir.y);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		dir += sf::Vector2f{ 0, -1 };
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		dir += sf::Vector2f{ 0, 1 };
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		dir += sf::Vector2f{ -1, 0 };
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		dir += sf::Vector2f{ 1, 0 };

	if(dir.x || dir.y)
		dir /= sqrt(dir.x * dir.x + dir.y * dir.y);

	std::cout << dir.x << '-' << dir.y << ',' << '\n';
	person.go(dir);
}