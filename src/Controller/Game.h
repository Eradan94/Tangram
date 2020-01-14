/**
 * Project Tangram
 */


#pragma once
#include "../View/Drawable.h"
#include "../View/Button.h"
#include "../Model/Shape.h"
#include "../Model/Piece.h"

#include <list>
#include <vector>
#include "../Model/Figure.h"

class Game {
public :
	static Game * init(const char * filename);

	Game();

	~Game();

	void draw(sf::RenderWindow& window);

	void select(const Point<double> & event);

	void deselect(const Point<double> & event);

	void centralizeSelected(const sf::Event::MouseMoveEvent event);

	void rotateSelected(const double d);

private :
    std::vector<Shape<double>*> pieces;
    std::list<Button> buttons;
	Shape<double> * selected;
	Point<double> relativePos;
	Figure * figure;
};
