/**
 * Project Tangram
 */


#pragma once
#include "../View/Drawable.h"
#include "../View/Button.h"
#include "../Model/Shape.h"
#include "../Model/Piece.h"
#include "../View/Menu.h"

#include <list>
#include <vector>
#include <cfloat>

class Game {
public :
	static Game * init(const char * filename);

	Game(Menu * menu, std::vector<Shape<double> *> pieces, Piece<double> * goal);

	~Game();

	void draw(sf::RenderWindow& window);

	void select(const Point<double> & event);

	void deselect(const Point<double> & event);

	void centralizeSelected(const sf::Event::MouseMoveEvent event);

	void rotateSelected(const double d);

	void save();

	void magnetize();

private :
    std::vector<Shape<double>*> pieces;
	Menu * menu;
	Shape<double> * selected;
	Point<double> relativePos;
	Piece<double> * goal;
	std::map<Point<double>, bool> validGoalPoints;
};
