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

	void addButton(Button * button);
	void draw(sf::RenderWindow & window);
private :
    std::vector<Button*> buttons;
};

