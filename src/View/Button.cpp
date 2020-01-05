/**
 * Project Tangram
 */


#include "Button.h"

#include <utility>

/**
 * Button implementation
 */

Button::Button(Point<int> topLeft, Point<int> bottomRight, string text) :
	topLeft(topLeft), bottomRight(bottomRight), text(std::move(text)), display(true) {
}

Button::Button(int topLeftX, int topLeftY, int bottomRightX, int bottomRightY, string text) :
	topLeft(Point<int>(topLeftX, topLeftY)), bottomRight(Point<int>(bottomRightX, bottomRightY)),
	text(std::move(text)), display(true) {
}

void Button::draw(sf::RenderWindow& window) {
    sf::RectangleShape rectangle;
    rectangle.setSize(sf::Vector2f(bottomRight.getX() - topLeft.getX(), bottomRight.getY() - topLeft.getY()));
    rectangle.setOutlineColor(sf::Color::White);
    rectangle.setOutlineThickness(5);
    rectangle.setPosition(bottomRight.getX(), bottomRight.getY());

    window.draw(rectangle);
}

void Button::setDisplay(bool mode) {
	display = mode;
}
