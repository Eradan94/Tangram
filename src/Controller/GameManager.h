#pragma once

#include "Game.h"
#include "ActionManager.h"

class GameManager {
public:
	//GameManager(const char * filename);
	GameManager();
	~GameManager();
	void draw() const;
	void play();

	bool isRunning();

	void initMainGameButtons();

	void initMainMenuButtons();

	void initCreateLevelButtons();

private:
	Game * game;
	Menu * menu;
	ActionManager * manager;
	sf::RenderWindow * window;
};
