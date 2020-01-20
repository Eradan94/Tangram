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
