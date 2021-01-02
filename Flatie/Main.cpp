#include <iostream>
#include <SFML/Graphics.hpp>

import Car;
import Person;



int main() {

    sf::ContextSettings(0, 0, 4);
    sf::RenderWindow window(sf::VideoMode(400, 400), "SFML testing");
    window.setFramerateLimit(144);
     
    Car car;
    Person person;

    sf::View view(sf::FloatRect(0.f, 0.f, window.getSize().x, window.getSize().y));
    view.setCenter(sf::Vector2f(.0f, .0f));
    view.zoom(.4f);
    window.setView(view);


    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            if(event.type == sf::Event::KeyPressed)
                if (event.key.code == sf::Keyboard::C) {
                    std::cout << 'a';
                    view.zoom(1.1f);
                    window.setView(view);
                }

            if (event.type == sf::Event::MouseWheelMoved) {
                float delta = (float)event.mouseWheel.delta;
                view.zoom(1 - (delta / 5));
                window.setView(view);
            }
        }


        window.clear();

        person.render(window);
        //steerACar(car);
        steerAPerson(person);
        //car.render(window);

        window.display();
    }

    return 0;
}