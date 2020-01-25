/**
 * Project Tangram
 */


#pragma once

#include <SFML/Graphics.hpp>
#include <map>
#define _USE_MATH_DEFINES
#include <math.h>
#include <iostream>
#include <functional>
#include "GameManager.h"
#include <string>

class Action {
public:
	Action(const function<void (sf::Event)> &fct);
	Action();
	void operator()(sf::Event);

	static void registerEvent(sf::Event::EventType event, const function<void (sf::Event)> action);
	static void initActions(Game & game, Menu& menu);
	static Action & getAction(sf::Event::EventType event);
private:
	inline static std::map<sf::Event::EventType, Action> actions;
	std::function<void (sf::Event)> fct;
};

