/**
 * Project Tangram
 */


#pragma once
#include "Drawable.h"
#include "Button.h"

#include <list>

class Menu: public Drawable {
public :
	Menu();
	~Menu();

	static Menu * init();

	void addButton(Button * button);
	void draw(sf::RenderWindow & window);
	void select(const Point<double> & event);
private :
    std::vector<Button*> buttons;
};

