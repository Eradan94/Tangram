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
	menu -> addButton(new Button(5, 975, 205, 1075, "Load"));
	menu -> addButton(new Button(205, 975, 405, 1075, "<<"));
	menu -> addButton(new Button(405, 975, 605, 1075, ">>"));
	menu -> addButton(new Button(605, 975, 805, 1075, "Options"));
	menu -> addButton(new Button(805, 975, 1005, 1075, "Clue"));
	menu -> addButton(new Button(1005, 975, 1205, 1075, "Quit"));
	return menu;
}
