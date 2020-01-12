/**
 * Project Tangram
 */


#pragma once

#include <SFML/Graphics.hpp>
#include <map>
#include <functional>
#include "Game.h"

class Action {
public:
	Action(const function<void (sf::Event)> &fct);
	Action();
	void operator()(sf::Event);

	static void registerEvent(sf::Event::EventType event, const function<void (sf::Event)> action);
	static void initActions(Game & game);
	static Action & getAction(sf::Event::EventType event);
private:
	inline static std::map<sf::Event::EventType, Action> actions;
	std::function<void (sf::Event)> fct;
};

