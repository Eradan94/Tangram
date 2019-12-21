/**
 * Project Tangram
 */


#ifndef _DRAWABLE_H
#define _DRAWABLE_H

#include <SFML/Graphics.hpp>

class Drawable {
    virtual void draw(sf::RenderWindow& window) = 0;
};

#endif //_DRAWABLE_H
