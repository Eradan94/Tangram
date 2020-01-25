#include "GameManager.h"
#include "Action.h"

GameManager::~GameManager() {
	delete game;
	delete menu;
	delete window;
}

GameManager::GameManager(const char *filename) : game(Game::init(filename)), menu(Menu::init()),
	window(new sf::RenderWindow(sf::VideoMode::getDesktopMode(), "Tangram")){
	Action::initActions(*game, *menu);
}

void GameManager::initMainMenuButtons() {
    //Here, initialize the main menu buttons
	menu -> addButton(new Button(5, 975, 205, 1075, "Load",
        []{
            std::cout << "Load" << std::endl;
        }
    ));
	menu -> addButton(new Button(205, 975, 405, 1075, "<<",
        []{
            std::cout << "<<" << std::endl;
        }
    ));
	menu -> addButton(new Button(405, 975, 605, 1075, ">>",
        []{
            std::cout << ">>" << std::endl;
        }
    ));
	menu -> addButton(new Button(605, 975, 805, 1075, "Options",
        []{
            std::cout << "Options" << std::endl;
        }
    ));
	menu -> addButton(new Button(805, 975, 1005, 1075, "Clue",
        []{
            std::cout << "Clue" << std::endl;
        }
    ));
	menu -> addButton(new Button(1005, 975, 1205, 1075, "Quit",
        []{
            std::cout << "Quit" << std::endl;
        }
    ));
}

void GameManager::draw() const {
    window->clear();
	if(game != nullptr) {
		game -> draw(*window);
	}
	if(menu != nullptr) {
		menu -> draw(*window);
	}
	window->display();
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
