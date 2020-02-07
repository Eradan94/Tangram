//
// Created by odomar on 20/01/2020.
//

#include "../../include/Controller/GameBuilder.h"

GameBuilder::GameBuilder() {

}

void GameBuilder::withShape(Shape<double> *shape) {
	pieces.push_back(shape);
}

Game *GameBuilder::build(const char * filename) {
	Piece<double> * goal = filename != nullptr ? Piece<double>::createPiece(filename) : nullptr;
	return new Game(pieces, goal);
}