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
	registerEvent(sf::Event::MouseButtonPressed, [&game](sf::Event event) {
		if (event.mouseButton.button == sf::Mouse::Left) {
			game.select(event.mouseButton);
			cout << "Pressed " << event.mouseButton.button << endl;
		}
	});
	registerEvent(sf::Event::MouseButtonReleased, [&game](sf::Event event) {
		if (event.mouseButton.button == sf::Mouse::Left) {
			game.deselect(event.mouseButton);
			cout << "Released " << event.mouseButton.x << " " << event.mouseButton.y << endl;
		}
	});
	registerEvent(sf::Event::MouseMoved, [&game](sf::Event event) {
		game.centralizeSelected(event.mouseMove);
		cout << "Moved " << event.mouseMove.x << " " << event.mouseMove.y << endl;
	});
	registerEvent(sf::Event::MouseWheelScrolled, [&game](sf::Event event) {
		game.rotateSelected(event.mouseWheelScroll.delta * M_PI / 16);
		cout << "Scrolled " << event.mouseWheelScroll.delta << endl;
	});
}

Action::Action() {
	fct = [](const sf::Event & event) {
		// Do nothing, default lambda for unregistered events
	};
}
