/**
 * Project Tangram
 */


#include "../../include/View/Menu.h"

Menu::Menu() {
}

void Menu::addButton(std::unique_ptr<Button> button) {
	buttons.push_back(std::move(button));
}

void Menu::setInputBox(std::unique_ptr<Button> inputBox) {
	this->inputBox = std::move(inputBox);
}

void Menu::draw(sf::RenderWindow & window) {
    for (auto & button : buttons) {
        button->draw(window);
    }
    for (auto & piece : decorationPieces) {
        piece->draw(window);
    }
    if(inputBox.get() != nullptr) {
        inputBox->draw(window);
    }
}

std::shared_ptr<Menu> Menu::init() {
	std::shared_ptr<Menu> menu = std::shared_ptr<Menu>(new Menu);
	return menu;
}

void Menu::clear() {
    buttons.clear();
    decorationPieces.clear();
    inputBox.reset();
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

void Menu::setText(char c) {
    if(inputBox.get() != nullptr) {
        inputBox->setText(c);
    }
}

std::string Menu::getInputBoxText() {
    return inputBox->getInputText();
}
