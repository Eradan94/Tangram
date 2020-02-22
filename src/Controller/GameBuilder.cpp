//
// Created by odomar on 20/01/2020.
//

#include "../../include/Controller/GameBuilder.h"

GameBuilder::GameBuilder() {

}

void GameBuilder::withShape(std::shared_ptr<Shape<double>> shape) {
	pieces.push_back(shape);
}

std::shared_ptr<Game> GameBuilder::build(const char * filename) {
	std::unique_ptr<Piece<double>> goal = filename != nullptr ? Piece<double>::createPiece(filename) : nullptr;
	return std::shared_ptr<Game>(new Game(pieces, std::move(goal)));
}
