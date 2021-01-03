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

sf::Vector2f trasformedPoint(sf::Shape* shape, size_t index) {
    return shape->getTransform().transformPoint(shape->getPoint(index));
}

export bool pointInShape(sf::Vector2f point, sf::Shape* shape) {
    sf::Vector2f first = trasformedPoint(shape, 0);
    sf::Vector2f second = trasformedPoint(shape, 1);


    for (int i = 2; i < shape->getPointCount(); i++)
        if (pointInTriangle(point, first, second, trasformedPoint(shape, i)))
            return true;
    return false;
}


export bool checkCollision(sf::Shape* shape, sf::Shape* other) {

    for (int i = 0; i < other->getPointCount(); i++)
        if (pointInShape(trasformedPoint(other, i), shape))
            return true;

    return false;
}