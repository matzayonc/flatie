#include <iostream>
#include <SFML/Graphics.hpp>

export module Collisions;




float sign(sf::Vector2f p1, sf::Vector2f p2, sf::Vector2f p3){
    return (p1.x - p3.x) * (p2.y - p3.y) - (p2.x - p3.x) * (p1.y - p3.y);
}

export bool pointInTriangle(sf::Vector2f pt, sf::Vector2f a, sf::Vector2f b, sf::Vector2f c){

    float d1 = sign(pt, a, b);
    float d2 = sign(pt, b, c);
    float d3 = sign(pt, c, a);

    //std::cout << "\na|" << d1 << '|' << d2 << '|' << d3;
    std::cout << "\nx|" << a.x << '|' << b.x << '|' << c.x;
    std::cout << "\ny|" << a.y << '|' << b.y << '|' << c.y;
    std::cout << "\np|" << pt.x << ',' << pt.y;

    bool has_neg = (d1 < 0) || (d2 < 0) || (d3 < 0);
    bool has_pos = (d1 > 0) || (d2 > 0) || (d3 > 0);

    return !(has_neg && has_pos);
}

/*
export bool pointInTriangle(sf::Vector2f pt, sf::Shape* other) {
    if (other->getPointCount() != 3) throw "not a triangle!";

    return pointInTriangle(pt, other->getPoint(0), other->getPoint(1), other->getPoint(2));
}
*/

export bool pointInShape(sf::Vector2f point, sf::Shape* shape) {
    sf::Vector2f first = shape->getPoint(0);
    sf::Vector2f second = shape->getPoint(0);


    for (int i = 2; i < shape->getPointCount(); i++)
        if (pointInTriangle(point, first, second, shape->getPoint(i)))
            return true;
    return false;
}


export void checkCollision(sf::Shape* shape, sf::Shape* other) {

    sf::Vector2f p = other->getTransform().transformPoint(other->getPoint(0));

}