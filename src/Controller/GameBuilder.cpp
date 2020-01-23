//
// Created by odomar on 20/01/2020.
//

#include "GameBuilder.h"

GameBuilder::GameBuilder() : menu(new Menu) {

}

void GameBuilder::withShape(Shape<double> *shape) {
	pieces.push_back(shape);
}

void GameBuilder::withButton(Button *button) {
	menu -> addButton(button);
}

Game *GameBuilder::build(const char * filename) {
	Piece<double> * goal = Piece<double>::createPiece(filename);
	return new Game(menu, pieces, goal);
}
