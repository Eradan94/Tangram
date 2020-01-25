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
 #include <cfloat>
#include <Menu.h>

class Game {
public :
	static Game * init(const char * filename);

	Game(std::vector<Shape<double> *> pieces, Piece<double> * goal);

	~Game();

	void draw(sf::RenderWindow& window);

	void select(const Point<double> & event);

	void deselect(const Point<double> & event);

	void centralizeSelected(const sf::Event::MouseMoveEvent event);

	void rotateSelected(const double d);

	void save();

	void magnetize();

	void checkValidatedGoalPoints();

private :
    std::vector<Shape<double>*> pieces;
	Shape<double> * selected;
	Point<double> relativePos;
	Piece<double> * goal;
	std::map<Point<double>, bool> validGoalPoints;
};
