#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>

#include "../../include/Controller/Game.h"
#include "../../include/Controller/Action.h"

#pragma once

class ActionManager {
public:
	ActionManager(std::shared_ptr<Game> game = nullptr, std::shared_ptr<Menu> menu = nullptr);

	void setGame(std::shared_ptr<Game> game);
	void setMenu(std::shared_ptr<Menu> menu);
	void registerEvent(sf::Event::EventType event, const std::function<void (sf::Event)> action);
	Action & getAction(sf::Event::EventType event);

private:
	std::map<sf::Event::EventType, Action> actions;
	std::shared_ptr<Game> game;
	std::shared_ptr<Menu> menu;
};

