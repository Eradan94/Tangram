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
	bool isPressed = false;
	Shape<double> *selected = nullptr;

	sf::RenderWindow window(sf::VideoMode(1600, 1000), "Tangram");

	while (window.isOpen())
	{
		sf::Event event{};
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
				isPressed = true;
				selected = game -> getSelected(event.mouseButton);
				cout << "Pressed " << selected << endl;
			}
			if(isPressed && event.type == sf::Event::MouseMoved) {
				if (selected != nullptr){
					selected->centralize(event.mouseMove);
					cout << "Moved " << event.mouseMove.x << " " << event.mouseMove.y << endl;
				}
			}
			if(isPressed && event.type == sf::Event::MouseWheelScrolled) {
				if (selected != nullptr){
					selected -> rotate(event.mouseWheelScroll.delta / 18);
					cout << "Scrolled " << event.mouseWheelScroll.delta << endl;
				}
			}
			if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
				isPressed = false;if (selected != nullptr){
					selected->centralize(event.mouseButton);
					cout << "Released " << event.mouseButton.x << " " << event.mouseButton.y << endl;
				}
			}
		}
		window.clear();
		game->draw(window);
		window.display();
	}

	return 0;
}
