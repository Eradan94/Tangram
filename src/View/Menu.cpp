/**
 * Project Tangram
 */


#include "../../include/View/Menu.h"

Menu::Menu() {
}

void Menu::addButton(std::unique_ptr<Button> button) {
	buttons.push_back(std::move(button));
}

void Menu::draw(sf::RenderWindow & window) {
    for (auto & button : buttons) {
        button->draw(window);
    }
    for (auto & piece : decorationPieces) {
        piece->draw(window);
    }
}

std::shared_ptr<Menu> Menu::init() {
	std::shared_ptr<Menu> menu = std::shared_ptr<Menu>(new Menu);
	return menu;
}

void Menu::clear() {
    buttons.clear();
    decorationPieces.clear();
}

void Menu::addDecorationPiece(std::shared_ptr<Shape<double>> piece) {
    decorationPieces.push_back(piece);
}

void Menu::select(const Point<double> & event) {
	for (auto& button : buttons) {
		if (button->isClicked(event)){
			button->callFct();
			return;
		}
	}
}
