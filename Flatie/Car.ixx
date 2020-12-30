#include <vector>
#include <cmath>
#include <SFML/Graphics.hpp>


export module Car;

namespace {
	const double piii = 2 * std::acos(0.0);

	float sinDeg(float degrees) {
		return std::sin(degrees * piii / 180);
	}

	float cosDeg(float degrees) {
		return std::cos(degrees * piii / 180);
	}
}


export class Car {
private:
	float speed = 0;
	float power = .03;
	float brakingPower = .05;
	float angle = 0;

	std::vector<sf::RectangleShape> shapes;


	void resetShapes() {
		shapes.clear();
		float w = 20;
		float h = 30;

		sf::RectangleShape body(sf::Vector2f(w, h));
		body.setOrigin(w / 2, 5);
		body.setPosition(50, 10);
		body.setFillColor(sf::Color::Cyan);

		shapes.push_back(body);
	}

public:
	Car() {
		resetShapes();
	}

	void gas() {
		speed += power;
	}

	void brake() {
		speed -= brakingPower;
		if (speed < 0)
			speed = 0;
	}

	void steer(float degrees) {
		if (!speed) return;

		angle += degrees;
	}

	void update() {
		sf::Vector2f d(sinDeg(-angle)*speed, cosDeg(-angle)*speed);

		for (auto& i : shapes) {
			i.setPosition(i.getPosition() + d);
			i.setRotation(angle);
		}
	}

	void render(sf::RenderWindow& window) {
		update();

		for (auto i : shapes)
			window.draw(i);
	}
};

