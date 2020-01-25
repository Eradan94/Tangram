#include "GameManager.h"
#include "Action.h"

GameManager::~GameManager() {
	delete game;
	delete menu;
	delete window;
}

GameManager::GameManager(const char *filename) : game(Game::init(filename)), menu(Menu::init()),
	window(new sf::RenderWindow(sf::VideoMode::getDesktopMode(), "Tangram")){
	Action::initActions(*game);
}

void GameManager::draw() const {
	if(game != nullptr) {
		game -> draw(*window);
	}
	if(menu != nullptr) {
		menu -> draw(*window);
	}
}

void GameManager::play() {
	sf::Event event{};
	while (window -> pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			window -> close();
		Action act = Action::getAction(event.type);
		act(event);
	}
	draw();
}

bool GameManager::isRunning() {
	return window -> isOpen();
}
