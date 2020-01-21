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

	Game(Menu * menu, std::vector<Shape<int> *> pieces, Piece<int> * goal);

	~Game();

	void draw(sf::RenderWindow& window);

	void select(const Point<int> & event);

	void deselect(const Point<int> & event);

	void centralizeSelected(const sf::Event::MouseMoveEvent event);

	void rotateSelected(const double d);

	void save();

	void magnetize();

	void checkValidatedGoalPoints();

private :
    std::vector<Shape<int>*> pieces;
	Menu * menu;
	Shape<int> * selected;
	Point<int> relativePos;
	Piece<int> * goal;
	std::map<Point<int>, bool> validGoalPoints;
};
