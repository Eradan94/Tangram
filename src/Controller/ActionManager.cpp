#include "ActionManager.h"

ActionManager::ActionManager(Game *game, Menu *menu) : game(game), menu(menu) {
	registerEvent(sf::Event::MouseButtonPressed, [*this](sf::Event event) {
		if (event.mouseButton.button == sf::Mouse::Left) {
			this -> menu -> select(event.mouseButton);
			this -> game -> select(event.mouseButton);
		}
	});
	registerEvent(sf::Event::MouseButtonReleased, [*this](sf::Event event) {
		if (event.mouseButton.button == sf::Mouse::Left) {
			this -> game -> deselect(event.mouseButton);
		}
	});
	registerEvent(sf::Event::MouseMoved, [*this](sf::Event event) {
		this -> game -> centralizeSelected(event.mouseMove);
	});
	registerEvent(sf::Event::MouseWheelScrolled, [*this](sf::Event event) {
		this -> game -> rotateSelected(event.mouseWheelScroll.delta * M_PI / 16);
	});
}

void ActionManager::registerEvent(sf::Event::EventType event, const function<void (sf::Event)> action) {
	actions.insert_or_assign(event, Action(action));
}

Action & ActionManager::getAction(sf::Event::EventType event) {
	return actions[event];
}

void ActionManager::setGame(Game * newGame) {
	game = newGame;
}

void ActionManager::setMenu(Menu * newMenu) {
	menu = newMenu;
}
