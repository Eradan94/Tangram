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
	Piece<double> * goal = Piece<double>::createPiece(filename);
	return new Game(pieces, goal);
}

Game *GameBuilder::build() {
	Piece<double> * goal = nullptr;
	return new Game(pieces, goal);
}
