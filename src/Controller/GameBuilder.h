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
	void withButton(Button * button);
	Game * build(const char * filename);

private:
	Menu * menu;
	std::vector<Shape<double> *> pieces;
};

