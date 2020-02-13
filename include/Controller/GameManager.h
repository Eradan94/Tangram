#pragma once

#include "../../include/Controller/Game.h"
#include "../../include/Controller/ActionManager.h"

#include <dirent.h>

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

	void initLoadGameButtons(int loadIndex);

	void initWinScreenButtons();

private:
	Game * game;
	Menu * menu;
	ActionManager * actionManager;
	sf::RenderWindow * window;
};
