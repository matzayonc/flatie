#include <iostream>
#include <SFML/Graphics.hpp>
#include "Point.hpp"
#include "Triangle.hpp"

export module Collisions;

gm::Point sfmlVectorToPoint(sf::Vector2f vector) {
    return gm::Point(vector.x, vector.y);
}

float sign(sf::Vector2f p1, sf::Vector2f p2, sf::Vector2f p3){
    //return (p1.x - p3.x) * (p2.y - p3.y) - (p2.x - p3.x) * (p1.y - p3.y);
    return (float)gm::Point(p1.x, p1.y).sideOfLine(gm::Point(p2.x, p2.y), gm::Point(p3.x, p3.y));
}

export bool pointInTriangle(sf::Vector2f pt, sf::Vector2f a, sf::Vector2f b, sf::Vector2f c) {
    gm::Triangle triangle(gm::Point(a.x, a.y), gm::Point(b.x, b.y), gm::Point(c.x, c.y));
    return triangle.contains(gm::Point(pt.x, pt.y));
}  
/*
export bool pointInTriangle(sf::Vector2f pt, sf::Vector2f a, sf::Vector2f b, sf::Vector2f c){

    gm::Point A(a.x, a.y);
    gm::Point B(b.x, b.y);
    gm::Point C(c.x, c.y);

    gm::Triangle tt(A, B, C);

    sf::Vector2f da(tt[0].x, tt[1].y);
    sf::Vector2f db(tt[1].x, tt[2].y);
    sf::Vector2f dc(tt[2].x, tt[0].y);

    if(A.x != tt[0].x || A.y != tt[0].y)
        std::cout << A << '-' << tt[0] << std::endl;


    float d1 = sign(pt, da, db);
    float d2 = sign(pt, db, dc);
    float d3 = sign(pt, dc, da);

    bool has_neg = (d1 < 0) || (d2 < 0) || (d3 < 0);
    bool has_pos = (d1 > 0) || (d2 > 0) || (d3 > 0);

    return !(has_neg && has_pos);
}*/


sf::Vector2f trasformedPoint(sf::Shape* shape, size_t index) {
    return shape->getTransform().transformPoint(shape->getPoint(index));
}

//FIXME
export bool pointInShape(sf::Vector2f point, sf::Shape* shape) {
    sf::Vector2f first = trasformedPoint(shape, 0);
    sf::Vector2f second = trasformedPoint(shape, shape->getPointCount()-1);

    for (int j = 1; j < shape->getPointCount()-1; j++)
        if (pointInTriangle(point, first, second, trasformedPoint(shape, j)))
            return true;
    
    for (int i = 1; i < shape->getPointCount(); i++) {
        first = trasformedPoint(shape, i-1);
        second = trasformedPoint(shape, i);

        for (int j = i; j < shape->getPointCount(); j++)
            if (pointInTriangle(point, first, second, trasformedPoint(shape, j)))
                return true;
    }

    return false;
}


bool lineAcrossLine(sf::Vector2f a, sf::Vector2f b, sf::Vector2f c, sf::Vector2f d)
{
    /*
    float denominator = ((b.x - a.x) * (d.y - c.y)) - ((b.y - a.y) * (d.x - c.x));
    float numerator1 = ((a.y - c.y) * (d.x - c.x)) - ((a.x - c.x) * (d.y - c.y));
    float numerator2 = ((a.y - c.y) * (b.x - a.x)) - ((a.x - c.x) * (b.y - a.y));

    // Detect coincident lines (has a problem, read below)
    if (denominator == 0) return numerator1 == 0 && numerator2 == 0;

    float r = numerator1 / denominator;
    float s = numerator2 / denominator;

    return (r >= 0 && r <= 1) && (s >= 0 && s <= 1);
    */

    gm::Point point(d.x, d.y);
    return point.doLinesCross(gm::Point(c.x, c.y), gm::Point(a.x, a.y), gm::Point(b.x, b.y));
}


bool lineAcrossShape(sf::Vector2f a, sf::Vector2f b, sf::Shape* shape) {

    for (int i = 1; i < shape->getPointCount(); i++)
        if (lineAcrossLine(a, b, trasformedPoint(shape, i-1), trasformedPoint(shape, i)))
            return true;
    return false;
}


export bool checkCollision(sf::Shape* shape, sf::Shape* other) {
    /*
    for (int i = 0; i < other->getPointCount(); i++)
        if (pointInShape(trasformedPoint(other, i), shape))
            return true;

    for (int i = 0; i < shape->getPointCount(); i++)
        if (pointInShape(trasformedPoint(shape, i), other))
            return true;*/
    
    for (int i = 1; i < other->getPointCount(); i++)
        if (lineAcrossShape(trasformedPoint(other, i-1), trasformedPoint(other, i), shape))
            return true;

    for (int i = 1; i < shape->getPointCount(); i++)
        if (lineAcrossShape(trasformedPoint(shape, i - 1), trasformedPoint(shape, i), other))
            return true;
    
    return false;
}