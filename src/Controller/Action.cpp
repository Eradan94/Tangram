/**
 * Project Tangram
 */


#include "../../include/Controller/Action.h"


Action::Action(const std::function<void (sf::Event)> &fct) : fct(fct) {}

void Action::operator()(sf::Event event) {
	fct(event);
}

Action::Action() {
	fct = [](const sf::Event & event) {
		// Do nothing, default lambda for unregistered events
	};
}
