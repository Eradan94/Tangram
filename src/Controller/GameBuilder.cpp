//
// Created by odomar on 20/01/2020.
//

#include "../../include/Controller/GameBuilder.h"

GameBuilder::GameBuilder() {

}

void GameBuilder::withShape(Shape<double> *shape) {
	pieces.push_back(shape);
}

std::shared_ptr<Game> GameBuilder::build(const char * filename) {
	Piece<double> * goal = filename != nullptr ? Piece<double>::createPiece(filename) : nullptr;
	return std::shared_ptr<Game>(new Game(pieces, goal));
}
