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


sf::Vector2f trasformedPoint(sf::Shape* shape, size_t index) {
    return shape->getTransform().transformPoint(shape->getPoint(index));
}

//FIXME
export bool pointInShape(sf::Vector2f point, sf::Shape* shape) {
    
    for (int i = 1; i < shape->getPointCount(); i++) {
        sf::Vector2f first = trasformedPoint(shape, i-1);
        sf::Vector2f second = trasformedPoint(shape, i);


        for (int j = i; j < shape->getPointCount(); j++)
            if (pointInTriangle(point, first, second, trasformedPoint(shape, j)))
                return true;
    }

    return false;
}


bool lineAcrossLine(sf::Vector2f a, sf::Vector2f b, sf::Vector2f c, sf::Vector2f d)
{
    float denominator = ((b.x - a.x) * (d.y - c.y)) - ((b.y - a.y) * (d.x - c.x));
    float numerator1 = ((a.y - c.y) * (d.x - c.x)) - ((a.x - c.x) * (d.y - c.y));
    float numerator2 = ((a.y - c.y) * (b.x - a.x)) - ((a.x - c.x) * (b.y - a.y));

    // Detect coincident lines (has a problem, read below)
    if (denominator == 0) return numerator1 == 0 && numerator2 == 0;

    float r = numerator1 / denominator;
    float s = numerator2 / denominator;

    return (r >= 0 && r <= 1) && (s >= 0 && s <= 1);
}


bool lineAcrossShape(sf::Vector2f a, sf::Vector2f b, sf::Shape* shape) {

    for (int i = 1; i < shape->getPointCount(); i++)
        if (lineAcrossLine(a, b, trasformedPoint(shape, i-1), trasformedPoint(shape, i)))
            return true;
    return false;
}


export bool checkCollision(sf::Shape* shape, sf::Shape* other) {

    for (int i = 0; i < other->getPointCount(); i++)
        if (pointInShape(trasformedPoint(other, i), shape))
            return true;

    for (int i = 0; i < shape->getPointCount(); i++)
        if (pointInShape(trasformedPoint(shape, i), other))
            return true;
    
    for (int i = 1; i < other->getPointCount(); i++)
        if (lineAcrossShape(trasformedPoint(other, i-1), trasformedPoint(other, i), shape))
            return true;

    for (int i = 1; i < shape->getPointCount(); i++)
        if (lineAcrossShape(trasformedPoint(shape, i - 1), trasformedPoint(shape, i), other))
            return true;
    
    return false;
}