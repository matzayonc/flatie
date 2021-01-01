
#include <vector>
#include <cmath>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>

export module Car;


namespace {
	const double piii = 2 * std::acos(0.0);

	float sinDeg(float degrees) {
		return (float)std::sin(degrees * piii / 180);
	}

	float cosDeg(float degrees) {
		return (float)std::cos(degrees * piii / 180);
	}
}


export class Car {
private:
	float speed = 0;
	float power = .03;
	float brakingPower = .05;
	float angle = 0;
	float dragCoeff = .01;
	bool reverse = false;
	
	float asGoodAsStopped = .01;

	sf::Time delayToReverse = sf::milliseconds(300);
	sf::Clock timeOfStop;

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

	void decelerate(float value) {
		if (!speed) return;

		float prev = speed;
		speed += speed > 0 ? -value : value;

		if (prev * speed < 0 || (speed && abs(speed) < asGoodAsStopped))
			stop();
	}

	void stop() {
		speed = 0;
		timeOfStop.restart();
	}


	bool canChangeReverse() {
		return !speed && timeOfStop.getElapsedTime() >= delayToReverse;
	}

public:
	Car() {
		resetShapes();
	}

	void gas() {
		speed += !reverse ? power : -power;
	}

	void brake() {
		decelerate(brakingPower);
	}

	void steer(float degrees) {
		angle += speed * degrees;
	}

	void update() {
		sf::Vector2f d(sinDeg(-angle)*speed, cosDeg(-angle)*speed);
		decelerate(dragCoeff * speed * speed);

		if (!speed && reverse)
			changeFromReverse();


		for (auto& i : shapes) {
			i.setPosition(i.getPosition() + d);
			i.setRotation(angle);
		}
	}

	void render(sf::RenderWindow& window) {
		update();

		for (const auto i : shapes)
			window.draw(i);
	}

	bool isStill() {
		return !speed;
	}

	bool isInReverse() {
		return reverse;
	}

	void changeToReverse() {
		if (!canChangeReverse()) return;
		
		timeOfStop.restart();
		reverse = true;
	}	
	
	void changeFromReverse() {
		if (!canChangeReverse()) return;

		timeOfStop.restart();
		reverse = false;
	}
};
