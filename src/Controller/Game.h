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

class Game: public Drawable {
public :
	static Game * init();

	void draw(sf::RenderWindow& window) override;

	Shape<double> * getSelected(Point<double> event);

private :
	Game();
    std::vector<Shape<double>*> pieces;
    std::list<Button> buttons;
};
