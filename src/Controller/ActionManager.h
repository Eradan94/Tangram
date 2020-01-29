#include "Game.h"
#include "Action.h"

#pragma once

class ActionManager {
public:
	ActionManager(Game * game = nullptr, Menu * menu = nullptr);
	void setGame(Game * game);
	void setMenu(Menu * menu);
	void registerEvent(sf::Event::EventType event, const function<void (sf::Event)> action);
	Action & getAction(sf::Event::EventType event);

	void testGame();
	void testMenu();

private:
	std::map<sf::Event::EventType, Action> actions;
	Game * game;
	Menu * menu;
};

