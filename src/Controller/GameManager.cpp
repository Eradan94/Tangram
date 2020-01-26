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

void GameManager::initMainGameButtons() {
    //Here, initialize the main game buttons
	menu -> addButton(new Button(5, 775, 205, 975, "Load",
        []{
            std::cout << "Load" << std::endl;
        }
    ));
	menu -> addButton(new Button(205, 775, 405, 975, "Save",
        [this]{
            std::cout << "Save" << std::endl;
            game -> save();
        }
    ));
	menu -> addButton(new Button(405, 775, 605, 975, "<<",
        []{
            std::cout << "<<" << std::endl;
        }
    ));
	menu -> addButton(new Button(605, 775, 805, 975, ">>",
        []{
            std::cout << ">>" << std::endl;
        }
    ));
	menu -> addButton(new Button(805, 775, 1005, 975, "Hint",
        []{
            std::cout << "Hint" << std::endl;
        }
    ));
	menu -> addButton(new Button(1005, 775, 1205, 975, "Option",
        []{
            std::cout << "Option" << std::endl;
        }
    ));
	menu -> addButton(new Button(1205, 775, 1405, 975, "Quit",
        [this]{
            std::cout << "Quit" << std::endl;
            window->close();
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
