//
// Created by odomar on 20/01/2020.
//

#include "GameBuilder.h"

GameBuilder::GameBuilder() : menu(new Menu) {

}

void GameBuilder::withShape(Shape<int> *shape) {
	pieces.push_back(shape);
}

void GameBuilder::withButton(Button *button) {
	menu -> addButton(button);
}

Game *GameBuilder::build(const char * filename) {
	Piece<int> * goal = Piece<int>::createPiece(filename);
	return new Game(menu, pieces, goal);
}
