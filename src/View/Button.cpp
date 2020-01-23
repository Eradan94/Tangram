/**
 * Project Tangram
 */


#include "Button.h"

#include <utility>

/**
 * Button implementation
 */

Button::Button(Point<double> topLeft, Point<double> bottomRight, string text) :
	topLeft(topLeft), bottomRight(bottomRight), text(std::move(text)), display(true)  {
	init();
}

Button::Button(int topLeftX, int topLeftY, int bottomRightX, int bottomRightY, string text) :
	topLeft(Point<double>(topLeftX, topLeftY)), bottomRight(Point<double>(bottomRightX, bottomRightY)),
	text(std::move(text)), display(true) {
	init();
}

void Button::draw(sf::RenderWindow& window) {
    window.draw(*rectangle);
	window.draw(*txt);
}

void Button::setDisplay(bool mode) {
	display = mode;
}

bool Button::isClicked(const Point<double> &p) const {
	return false;
}

void Button::init() {
	rectangle = new sf::RectangleShape;
	rectangle -> setSize(sf::Vector2f(bottomRight.getX() - topLeft.getX(), bottomRight.getY() - topLeft.getY()));
	rectangle -> setFillColor(sf::Color::Black);
	rectangle -> setOutlineColor(sf::Color::White);
	rectangle -> setOutlineThickness(5);
	rectangle -> setPosition(topLeft.getX(), topLeft.getY());

	sf::Font * font = new sf::Font;
	if (!font -> loadFromFile("fonts/LiberationSans-Regular.ttf"))
	{
		cerr << "unable to load font" << endl;
		exit(1);
	}

	txt = new sf::Text;
	txt -> setFont(*font);
	txt -> setFillColor(sf::Color::White);
	txt -> setString(text);
	txt -> setCharacterSize(50);

	sf::FloatRect rect = txt -> getGlobalBounds();
	int posX = topLeft.getX() + (bottomRight.getX() - topLeft.getX()) / 2;
	int posY = topLeft.getY() + (bottomRight.getY() - topLeft.getY()) / 2;

	txt -> setOrigin(rect.left + rect.width / 2, rect.top + rect.height / 2);
	txt -> setPosition(posX, posY);
}

Button::~Button() {
	delete rectangle;
	delete txt->getFont();
	delete txt;
}
