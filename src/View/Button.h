/**
 * Project Tangram
 */


#pragma once
#include <SFML/Graphics.hpp>

#include "Drawable.h"
#include "../Controller/Clickable.h"
#include "../Model/Point.h"


class Button: public Drawable, public Clickable<int> {
public :
    Button(Point<int> topLeft, Point<int> bottomRight, string text);
    Button(int topLeftX, int topLeftY, int bottomRightX, int bottomRightY, string text);

    void setDisplay(bool mode);
    void draw(sf::RenderWindow& window) override;
    bool isClicked(const Point<int>& p) const;

private :
    Point<int> topLeft;
    Point<int> bottomRight;
    string text;
    bool display;
};

