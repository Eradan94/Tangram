/**
 * Project Tangram
 */


#pragma once
#include <SFML/Graphics.hpp>
#include <functional>
#include <memory>

#include "../../include/View/Drawable.h"
#include "../../include/Controller/Clickable.h"
#include "../../include/Model/Point.h"


class Button: public Drawable, public Clickable<double> {
public :
    Button(int topLeftX, int topLeftY, int bottomRightX, int bottomRightY, std::string text, std::function<void()> _fct);
    ~Button();

    void callFct();
    void draw(sf::RenderWindow& window) override;
    bool isClicked(const Point<double>& p) const override;
    Point<double> center() const;

private :
    Point<double> topLeft;
    Point<double> bottomRight;
    std::string text;
	std::function<void ()> fct;
	std::unique_ptr<sf::RectangleShape> rectangle;
	std::unique_ptr<sf::Text> txt;
};
