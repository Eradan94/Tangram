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
	void withShape(Shape<int> * shape);
	void withButton(Button * button);
	Game * build(const char * filename);

private:
	Menu * menu;
	std::vector<Shape<int> *> pieces;
};

