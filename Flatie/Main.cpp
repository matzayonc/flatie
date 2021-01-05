#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>

#include "Point.hpp"
#include "Vector.hpp"


import Entity;
import Car;
import Person;
import Collisions;


int main() {
    gm::Point point(1, 2);



    sf::ContextSettings(0, 0, 4);
    sf::RenderWindow window(sf::VideoMode(400, 400), "SFML testing");
    window.setFramerateLimit(144);


    sf::Font fontHack;
    if (!fontHack.loadFromFile("data/fonts/Hack.ttf"))
        throw "could not load font";

    int points = 0;
    bool inside = true;

    sf::Text counterText;
    counterText.setFont(fontHack);
    counterText.setString("points");
    counterText.setCharacterSize(14);
    counterText.setFillColor(sf::Color::White);



    Car car;
    Person person;

    Person obstacle;


    sf::View view(sf::FloatRect(0.f, 0.f, (float)window.getSize().x, (float)window.getSize().y));
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
                if (event.type == sf::Event::Resized){
                    sf::FloatRect visibleArea(0.f, 0.f, (float)event.size.width, (float)event.size.height);
                    window.setView(sf::View(visibleArea));
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
            car.steer();
            car.render(window);
        }
        else {
            car.render(window);
            person.steer();
            person.render(window);

        }

        if (obstacle.collides(car) || obstacle.collides(person)) {
            if(!inside)
                points++;

            inside = true;
        }
        else {
            inside = false;
            obstacle.render(window);
        }

        

        window.setView(window.getDefaultView());
        counterText.setString(std::to_string(points));
        window.draw(counterText);
        window.setView(view);
        window.display();
    }

    return 0;
}