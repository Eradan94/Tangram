/**
 * Project Tangram
 */


#include "../../include/View/Button.h"

#include <utility>

/**
 * Button implementation
 */

Button::Button(int topLeftX, int topLeftY, int bottomRightX, int bottomRightY, string text, std::function<void()> _fct) :
	topLeft(Point<double>(topLeftX, topLeftY)), bottomRight(Point<double>(bottomRightX, bottomRightY)), fct(_fct),
	text(std::move(text)) {
	rectangle = std::unique_ptr<sf::RectangleShape>(new sf::RectangleShape);
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

	txt = std::unique_ptr<sf::Text>(new sf::Text);
	txt -> setFont(*font);
	txt -> setFillColor(sf::Color::White);
	txt -> setString(this -> text);
	txt -> setCharacterSize(50);

	sf::FloatRect rect = txt -> getGlobalBounds();
	int posX = topLeft.getX() + (bottomRight.getX() - topLeft.getX()) / 2;
	int posY = topLeft.getY() + (bottomRight.getY() - topLeft.getY()) / 2;

	txt -> setOrigin(rect.left + rect.width / 2, rect.top + rect.height / 2);
	txt -> setPosition(posX, posY);
}

void Button::draw(sf::RenderWindow& window) {
    window.draw(*rectangle);
	window.draw(*txt);
}

bool Button::isClicked(const Point<double> &p) const {
    return(p.getX() >= topLeft.getX() && p.getX() <= bottomRight.getX() && p.getY() >= topLeft.getY() && p.getY() <= bottomRight.getY());
}

void Button::callFct() {
    std::function<void ()> c = fct;
    c();
}

Button::~Button() {
	//delete rectangle;
	//delete txt->getFont();
	//delete txt;
}

Point<double> Button::center() {
    double length = bottomRight.getX() - topLeft.getX();
    double height = bottomRight.getY() - topLeft.getY();
    return Point(topLeft.getX() + length / 2, topLeft.getY() + height / 2);
}
