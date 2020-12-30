#include <iostream>
#include <SFML/Graphics.hpp>

import Car;



int main() {

    sf::ContextSettings(0, 0, 4);
    sf::RenderWindow window(sf::VideoMode(400, 400), "SFML testing");
    window.setFramerateLimit(144);

    Car car;


    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
            car.gas();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
            car.brake();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
            car.steer(-1);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            car.steer(1);

        window.clear();

        car.render(window);

        window.display();
    }

    return 0;
}