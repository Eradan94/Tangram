/*!
 * \file Drawable.h
 * \brief Interface for drawable elements
 * \author Biguenet Denis & Gosset Severin
 * \date 22/02/2020
 */

#pragma once
#include <SFML/Graphics.hpp>

/*! \interface Drawable
 * \brief Interface for drawable elements
 *
 */
class Drawable {
public:
    /*!
     * \brief Draw method
     * \param window : SFML window where the element is draw
     *
     */
    virtual void draw(sf::RenderWindow& window) = 0;
};

