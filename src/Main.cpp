/**
 * Project Tangram
 */

#include <SFML/Graphics.hpp>

#include "Model/Point.h"
#include "Model/Piece.h"

#include <iostream>
#include <vector>
#include "Controller/Action.h"
#include "Controller/Game.h"

using namespace std;

int main(int argc, char const *argv[]) {
	Game * game = Game::init(argv[1]);

	sf::RenderWindow window(sf::VideoMode(900, 800), "Tangram");
	Action::initActions(*game);

	while (window.isOpen())
	{
		sf::Event event{};
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			Action act = Action::getAction(event.type);
			act(event);
		}
		game->draw(window);
	}
	delete game;
	return 0;
}
