#include <vector>
#include <iostream>
#include <SFML/Graphics.hpp>

export module Person;
import Entity; 


export class Person : public Entity {
private:
	sf::Vector2f direction{ 0, 0 };
	float speed = 1e1f;

	void resetShapes() override {
		shapes.push_back(std::make_shared<sf::CircleShape>(.5f, 30));
		shapes[shapes.size()-1]->setOrigin(3, 3);
		shapes[shapes.size()-1]->setFillColor(sf::Color::Red);

		hitboxFromShapes();
	}

	void update() {
		float dTime = tick();
		move(dTime * speed * direction.x, dTime * speed * direction.y);
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

	void steer() {
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

		if (dir.x && dir.y)
			dir /= sqrt(dir.x * dir.x + dir.y * dir.y);

		go(dir);
	}
};
