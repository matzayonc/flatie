#include <iostream>
#include <SFML/Graphics.hpp>

import Car;
import Person;
import Collisions;



int main() {

    sf::ContextSettings(0, 0, 4);
    sf::RenderWindow window(sf::VideoMode(400, 400), "SFML testing");
    window.setFramerateLimit(144);

    
     
    Car car;
    Person person;

    Person obstacle;


    sf::View view(sf::FloatRect(0.f, 0.f, window.getSize().x, window.getSize().y));
    view.setCenter(sf::Vector2f(.0f, .0f));
    view.zoom(.2f);
    window.setView(view);

    bool inCar = false;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::C) {
                    std::cout << 'a';
                    view.zoom(1.1f);
                    window.setView(view);
                }
                if (event.key.code == sf::Keyboard::E) {
                    std::cout << car.collides(person) << '\n';

                    if (!inCar && car.collides(person))
                        inCar = true;
                    else if(inCar){
                        person.teleport(car.getCoords() + sf::Vector2f{2.f, 2.f});
                        inCar = false;

                    }
                }

            }

            if (event.type == sf::Event::MouseWheelMoved) {
                float delta = (float)event.mouseWheel.delta;
                view.zoom(1 - (delta / 5));
                window.setView(view);
            }
        }


        window.clear();


        if (inCar) {
            steerACar(car);
            car.render(window);
        }
        else {
            car.render(window);
            steerAPerson(person);
            person.render(window);

        }

        if (obstacle.collides(car) || obstacle.collides(person)) {
            std::cout << "+1\n";
        }
        else
        obstacle.render(window);

        

        window.display();
    }

    return 0;
}