//
// Created by odomar on 20/01/2020.
//

#pragma once

#include "../Model/Shape.h"
#include "../View/Button.h"
#include "Game.h"

class GameBuilder {
public:
	GameBuilder();
	void withShape(Shape<double> * shape);
	Game * build(const char * filename);
	Game * build();

private:
	std::vector<Shape<double> *> pieces;
};

