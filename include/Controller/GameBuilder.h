//
// Created by odomar on 20/01/2020.
//

#pragma once

#include "../../include/Model/Shape.h"
#include "../../include/View/Button.h"
#include "../../include/Controller/Game.h"

class GameBuilder {
public:
	GameBuilder();
	void withShape(Shape<double> * shape);
	std::shared_ptr<Game> build(const char * filename);
	std::shared_ptr<Game> build();

private:
	std::vector<Shape<double> *> pieces;
};

