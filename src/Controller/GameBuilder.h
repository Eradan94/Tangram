//
// Created by odomar on 20/01/2020.
//

#pragma once

#include <Shape.h>
#include <Button.h>
#include "Game.h"

class GameBuilder {
public:
	GameBuilder();
	void withShape(Shape<double> * shape);
	Game * build(const char * filename);

private:
	std::vector<Shape<double> *> pieces;
};

