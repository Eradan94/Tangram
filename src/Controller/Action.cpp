/**
 * Project Tangram
 */


#include "Action.h"

void Action::registerEvent(sf::Event::EventType event, const function<void (sf::Event)> action) {
	Action::actions.insert_or_assign(event, Action(action));
}

Action & Action::getAction(sf::Event::EventType event) {
	return Action::actions[event];
}

Action::Action(const function<void (sf::Event)> &fct) : fct(fct) {}

void Action::operator()(sf::Event event) {
	fct(event);
}

void Action::initActions(Game & game) {
	registerEvent(sf::Event::Closed, [&game](sf::Event event) {
		game.save();
	});
	registerEvent(sf::Event::MouseButtonPressed, [&game](sf::Event event) {
		if (event.mouseButton.button == sf::Mouse::Left) {
			game.select(event.mouseButton);
		}
	});
	registerEvent(sf::Event::MouseButtonReleased, [&game](sf::Event event) {
		if (event.mouseButton.button == sf::Mouse::Left) {
			game.deselect(event.mouseButton);
		}
	});
	registerEvent(sf::Event::MouseMoved, [&game](sf::Event event) {
		game.centralizeSelected(event.mouseMove);
	});
	registerEvent(sf::Event::MouseWheelScrolled, [&game](sf::Event event) {
		game.rotateSelected(event.mouseWheelScroll.delta * 3.14 / 16);
	});
}

Action::Action() {
	fct = [](const sf::Event & event) {
		// Do nothing, default lambda for unregistered events
	};
}
