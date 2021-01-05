
#include <vector>
#include <cmath>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>

export module Car;
import Entity;
import Collisions;

namespace {
	const double pi = 2 * std::acos(0.0);

	float sinDeg(float degrees) {
		return (float)std::sin(degrees * pi / 180);
	}

	float cosDeg(float degrees) {
		return (float)std::cos(degrees * pi / 180);
	}
}

export class Car:public Entity {
private:
	float speed = 0;
	float power = 1e2f;
	float brakingPower = 1e2;
	float steeringAngle = 0;
	float angle = 270;
	float dragCoeff = .02f;
	bool reverse = false;

	float asGoodAsStopped = 1e-2f;

	sf::Time delayToReverse = sf::milliseconds(300);
	sf::Clock timeOfStop;


	void resetShapes() {
		shapes.clear();
		float w = 3;
		float h = 5;

		auto body = std::make_shared<sf::RectangleShape>(sf::Vector2f(w, h));
		body->setOrigin(w / 2, .5f);
		body->setPosition(5, 5);
		body->setFillColor(sf::Color::Cyan);

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
	bool gasing = false;
	bool braking = false;


	Car() {
		resetShapes();
	}


	void turn(float degrees) {
		steeringAngle += degrees;
	}

	void update() {
		float deltaT = tick();
		sf::Vector2f d(sinDeg(-angle)*speed*deltaT, cosDeg(-angle)*speed*deltaT);
		decelerate(dragCoeff * speed * speed * deltaT);

		angle += speed * steeringAngle * deltaT * 5e-1f;
		steeringAngle = 0;

		std::cout << deltaT << '\n';

		if (!speed && reverse)
			changeFromReverse();

		if(braking)
			decelerate(brakingPower*deltaT);

		if(gasing)
			speed += (!reverse ? 1 : -1) * power * deltaT;

		for (auto& i : shapes) {
			i->setPosition(i->getPosition() + d);
			i->setRotation(angle);
		}
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

	void steer() {

		bool s = sf::Keyboard::isKeyPressed(sf::Keyboard::S);
		bool w = sf::Keyboard::isKeyPressed(sf::Keyboard::W);

		if (isStill() && s)
			changeToReverse();

		if (!isInReverse()) {
			gasing = w;
			braking = s;
		}
		else {
			braking = w;
			gasing = s;
		}


		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
			turn(-10);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			turn(10);
	}
};
