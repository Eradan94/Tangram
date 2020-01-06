/**
 * Project Tangram
 */

#include <SFML/Graphics.hpp>

#include "Model/Point.h"
#include "Model/Piece.h"

#include <iostream>
#include <vector>
#include <Game.h>

using namespace std;

int main(int argc, char const *argv[]) {
	Game * game = Game::init();

	sf::RenderWindow window(sf::VideoMode(1600, 1000), "SFML works!");

	while (window.isOpen())
	{
		sf::Event event{};
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		window.clear();
		game->draw(window);
		window.display();
	}

	return 0;
}
