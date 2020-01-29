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
	for (auto button : buttons){
		delete button;
	}
}

Menu *Menu::init() {
	auto * menu = new Menu;
	return menu;
}

void Menu::clear() {
//    for (auto button : buttons){
//		delete button;
//	} //BUG
    buttons.clear();
}

void Menu::select(const Point<double> & event) {
	for (auto button : buttons) {
		if (button->isClicked(event)){
			button->callFct();
			return;
		}
	}
}
