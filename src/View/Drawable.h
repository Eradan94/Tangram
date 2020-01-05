/**
 * Project Tangram
 */


#pragma once
#include <SFML/Graphics.hpp>

class Drawable {
public:
    virtual void draw(sf::RenderWindow& window) = 0;
};

