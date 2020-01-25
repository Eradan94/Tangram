/**
 * Project Tangram
 */


#pragma once
#include <SFML/Graphics.hpp>
#include <functional>

#include "Drawable.h"
#include "../Controller/Clickable.h"
#include "../Model/Point.h"


class Button: public Drawable, public Clickable<double> {
public :
    Button(Point<double> topLeft, Point<double> bottomRight, string text);
    Button(int topLeftX, int topLeftY, int bottomRightX, int bottomRightY, string text, std::function<void()> _fct);
    ~Button();

    void setDisplay(bool mode);
    void draw(sf::RenderWindow& window) override;
    bool isClicked(const Point<double>& p) const override;

private :
	void init();
    Point<double> topLeft;
    Point<double> bottomRight;
    string text;
	std::function<void ()> fct;
    bool display;
	sf::RectangleShape * rectangle;
	sf::Text * txt;
};
