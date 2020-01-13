/**
 * Project Tangram
 */


#include "../Model/Triangle.h"
#include "Game.h"
#include "../Model/Piece.h"
#include "Action.h"

Game * Game::init() {
	auto * smallTriangle1 = new Piece<double>(1, sf::Color(255, 100, 0),
											  0.0, 400.0, 100.0, 300.0, 200.0, 400.0);
	auto * smallTriangle2 = new Piece<double>(1, sf::Color(255, 255, 0),
											  200.0, 200.0, 300.0, 100.0, 300.0, 300.0);
	auto * mediumTriangle = new Piece<double>(1, sf::Color(0, 255, 0),
											  200.0, 400.0, 400.0, 200.0, 400.0, 400.0);
	auto * largeTriangle1 = new Piece<double>(1, sf::Color(150, 0, 100),
											  0.0, 0.0, 200.0, 200.0, 0.0, 400.0);
	auto * largeTriangle2 = new Piece<double>(1, sf::Color(255, 0, 150),
											  0.0, 0.0, 400.0, 0.0, 200.0, 200.0);
	auto * square = new Piece<double>(2, sf::Color(0, 0, 255),
											  100.0, 300.0, 200.0, 200.0, 200.0, 400.0,
											  200.0, 200.0, 300.0, 300.0, 200.0, 400.0);
	auto * parallelogram = new Piece<double>(2, sf::Color(0, 255, 255),
											  300.0, 100.0, 400.0, 0.0, 400.0, 200.0,
											  300.0, 100.0, 400.0, 200.0, 300.0, 300.0);

	Game * game = new Game;
	game->pieces.push_back(smallTriangle1);
	game->pieces.push_back(smallTriangle2);
	game->pieces.push_back(mediumTriangle);
	game->pieces.push_back(largeTriangle1);
	game->pieces.push_back(largeTriangle2);
	game->pieces.push_back(square);
	game->pieces.push_back(parallelogram);
	// boutons :
	// ???
	return game;
}

Game::Game() : selected(nullptr), relativePos(Point(0., 0.)) {
}

void Game::draw(sf::RenderWindow& window) {
	window.clear();
	for (auto s : pieces) {
		s -> draw(window);
	}
	window.display();
}

void Game::select(const Point<double> & event) {
	selected = nullptr;
	for (auto s : pieces) {
		if (s->isClicked(event)){
			selected = s;
			relativePos = selected->center() - event;
		}
	}
}

void Game::deselect(const Point<double> & event) {
	if (selected != nullptr) {
		selected->centralize(event, relativePos);
		selected = nullptr;
	}
}

void Game::centralizeSelected(sf::Event::MouseMoveEvent event) {
	if (selected != nullptr) {
		selected -> centralize(event, relativePos);
	}
}

void Game::rotateSelected(const double d) {
	selected -> rotate(d);
}

Game::~Game() {
}
