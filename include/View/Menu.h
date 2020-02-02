/**
 * Project Tangram
 */


#pragma once
#include "../../include/View/Drawable.h"
#include "../../include/View/Button.h"

#include <list>

class Menu: public Drawable {
public :
	Menu();
	~Menu();

	static Menu * init();

	void addButton(Button * button);
	void draw(sf::RenderWindow & window);
	void select(const Point<double> & event);
	void clear();
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
};

