#pragma once

#include "Game.h"

class GameManager {
public:
	GameManager(const char * filename);
	~GameManager();
	void draw() const;
	void play();

	bool isRunning();

	void initMainGameButtons();

private:
	Game * game;
	Menu * menu;
	sf::RenderWindow * window;
};
