/**
 * Project Tangram
 */


#pragma once
#include "../../include/View/Drawable.h"
#include "../../include/View/Button.h"
#include "../../include/Model/Shape.h"
#include "../../include/Model/Piece.h"

#include <list>
#include <memory>

class Menu: public Drawable {
public :
	Menu();
	static std::shared_ptr<Menu> init();

	void addButton(std::unique_ptr<Button> button);
	void draw(sf::RenderWindow & window);
	void select(const Point<double> & event);
	void clear();
	void addDecorationPiece(std::shared_ptr<Shape<double>> piece);
private :
    std::vector<std::unique_ptr<Button>> buttons;
    std::vector<std::shared_ptr<Shape<double>>> decorationPieces;
};

