#pragma once

#include "../../include/Controller/Game.h"
#include "../../include/Controller/ActionManager.h"

#include <dirent.h>

class GameManager {
public:
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
    std::shared_ptr<Menu> menu;
	std::shared_ptr<Game> game;
	ActionManager * actionManager;
	sf::RenderWindow * window;
};
