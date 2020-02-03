/**
 * Project Tangram
 */


#pragma once
#include "../../include/View/Drawable.h"
#include "../../include/View/Button.h"
#include "../../include/Model/Shape.h"
#include "../../include/Model/Piece.h"
#include "../../include/View/Menu.h"

#include <list>
#include <vector>
#include <cfloat>

class Game {
public :
	static Game * init(const char * filename);

	static Game * init();

	Game(std::vector<Shape<double> *> pieces, Piece<double> * goal);

	Game();

	~Game();

	void draw(sf::RenderWindow& window);

	void select(const Point<double> & event);

	void deselect(const Point<double> & event);

	void centralizeSelected(const sf::Event::MouseMoveEvent event);

	void rotateSelected(const double d);

	void save();

	void magnetize();

	void validateShape();

	bool getGameState();

private :
    std::vector<Shape<double>*> pieces;
	Shape<double> * selected;
	Point<double> relativePos;
	Piece<double> * goal;
	bool gameState;
};
