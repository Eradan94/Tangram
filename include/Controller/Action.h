/**
 * Project Tangram
 */

#pragma once

#include <SFML/Graphics.hpp>
#include <map>
#include <math.h>
#include <iostream>
#include <functional>
#include <string>

class Action {
public:
	Action(const std::function<void (sf::Event)> &fct);
	Action();
	void operator()(sf::Event);

private:
	std::function<void (sf::Event)> fct;
};

