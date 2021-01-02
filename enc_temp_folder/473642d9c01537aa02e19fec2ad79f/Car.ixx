
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
	float power = 1e2f;
	float brakingPower = 1e3;
	float steeringAngle = 0;
	float angle = 0;
	float dragCoeff = .02f;
	bool reverse = false;

	float asGoodAsStopped = 1e-2f;

	sf::Time delayToReverse = sf::milliseconds(300);
	sf::Clock timeOfStop;
	sf::Clock tick;

	std::vector<sf::RectangleShape> shapes;


	void resetShapes() {
		shapes.clear();
		float w = 3;
		float h = 5;

		sf::RectangleShape body(sf::Vector2f(w, h));
		body.setOrigin(w / 2, .5f);
		body.setPosition(5, 5);
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
	bool gasing = false;
	bool braking = false;


	Car() {
		resetShapes();
	}


	void steer(float degrees) {
		steeringAngle += degrees;
	}

	void update() {
		float deltaT = (float)tick.getElapsedTime().asMicroseconds() / 1e6f;
		tick.restart();

		sf::Vector2f d(sinDeg(-angle)*speed*deltaT, cosDeg(-angle)*speed*deltaT);
		decelerate(dragCoeff * speed * speed * deltaT);

		angle += speed * steeringAngle * deltaT * 5e-1;
		steeringAngle = 0;


		if (!speed && reverse)
			changeFromReverse();

		if(braking)
			decelerate(brakingPower);

		if(gasing)
			speed += (!reverse ? 1 : -1) * power * deltaT;


		std::cout << "speed: " << deltaT << '\n';

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


export void steerACar(Car& car) {

	bool s = sf::Keyboard::isKeyPressed(sf::Keyboard::S);
	bool w = sf::Keyboard::isKeyPressed(sf::Keyboard::W);

	if (car.isStill() && s)
		car.changeToReverse();

	if (!car.isInReverse()) {
		car.gasing = w;
		car.braking = s;
	}
	else {
		car.braking = w;
		car.gasing = s;
	}


	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		car.steer(-10);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		car.steer(10);
}