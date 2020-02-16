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
	~Menu();

	static std::shared_ptr<Menu> init();

	void addButton(Button * button);
	void draw(sf::RenderWindow & window);
	void select(const Point<double> & event);
	void clear();
	void addDecorationPiece(Piece<double>* piece);
	friend std::ostream& operator<< (std::ostream& os, const Menu& menu) {
	    os << "menu : " << std::endl;
	    os << menu.buttons.size() << std::endl;
        for(Button* b : menu.buttons) {
            os << *b << std::endl;
        }
        return os;
    }
private :
    std::vector<Button*> buttons;
    std::vector<Shape<double> *> decorationPieces;
};

