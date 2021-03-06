#include "../../include/Controller/ActionManager.h"

ActionManager::ActionManager(std::shared_ptr<Game> game, std::shared_ptr<Menu> menu) : game(game), menu(menu) {
	registerEvent(sf::Event::MouseButtonPressed, [this](sf::Event event) {
		if (event.mouseButton.button == sf::Mouse::Left) {
			if (this -> menu != nullptr) {
				this -> menu -> select(event.mouseButton);
			}
			if (this -> game != nullptr) {
				this -> game -> select(event.mouseButton);
			}
		}
	});
	registerEvent(sf::Event::MouseButtonReleased, [this](sf::Event event) {
		if (event.mouseButton.button == sf::Mouse::Left) {
			if (this -> game != nullptr){
				this -> game -> deselect();
				this -> game -> validateShape();
			}
		}
	});
	registerEvent(sf::Event::MouseMoved, [this](sf::Event event) {
		if (this -> game != nullptr){
			this -> game -> centralizeSelected(event.mouseMove);
		}
	});
	registerEvent(sf::Event::MouseWheelScrolled, [this](sf::Event event) {
		if (this -> game != nullptr) {
            Preferences * pref = Preferences::getInstance();
			this -> game -> rotateSelected(event.mouseWheelScroll.delta * pref -> getRotationPerSpinning());
		}
	});
	registerEvent(sf::Event::TextEntered, [this](sf::Event event) {
		this -> menu -> setText((char)event.text.unicode);
	});
}

void ActionManager::registerEvent(sf::Event::EventType event, const std::function<void (sf::Event)> action) {
	actions.insert_or_assign(event, Action(action));
}

Action & ActionManager::getAction(sf::Event::EventType event) {
	return actions[event];
}

void ActionManager::setGame(std::shared_ptr<Game> newGame) {
	game = newGame;
}

void ActionManager::setMenu(std::shared_ptr<Menu> newMenu) {
	menu = newMenu;
}
