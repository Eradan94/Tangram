#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>

#include "../../include/Controller/Game.h"
#include "../../include/Controller/Action.h"

#pragma once

class ActionManager {
public:
	ActionManager(Game * game = nullptr, Menu * menu = nullptr);
	void setGame(Game * game);
	void setMenu(Menu * menu);
	void registerEvent(sf::Event::EventType event, const function<void (sf::Event)> action);
	Action & getAction(sf::Event::EventType event);

private:
	std::map<sf::Event::EventType, Action> actions;
	Game * game;
	Menu * menu;
};

