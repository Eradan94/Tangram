/**
 * Project Tangram
 */


#include "Menu.h"

Menu::Menu() {

}

void Menu::addButton(Button * button) {
	buttons.push_back(button);
}

void Menu::draw(sf::RenderWindow & window) {
	for (auto & button : buttons) {
		button->draw(window);
	}
}

Menu::~Menu() {
	for (auto * button : buttons){
		delete button;
	}
}

Menu *Menu::init() {
	auto * menu = new Menu;
	menu -> addButton(new Button(1200, 50, 1425, 175, "<<"));
	menu -> addButton(new Button(1450, 50, 1700, 175, ">>"));
	menu -> addButton(new Button(1200, 200, 1425, 325, "Load"));
	menu -> addButton(new Button(1450, 200, 1700, 325, "Save"));
	menu -> addButton(new Button(1200, 350, 1700, 475, "Quit"));
	return menu;
}
