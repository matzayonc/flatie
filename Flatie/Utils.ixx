export module Utils;

#include "Vector.hpp"
#include "SFML/Graphics.hpp"

export gm::Vector sfmlVectorTogmVector(sf::Vector2f v) {
	return gm::Vector(v.x, v.y);
}