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
    const int width = window->getView().getSize().x;
    const int height = window->getView().getSize().y;
    const int buttonCount = 7;
	const int buttonOutline = 5;
    const int buttonWidth = (width - 2 * buttonOutline) / buttonCount;
    const int buttonHeight = 0.1 * height;
	menu -> addButton(new Button(buttonOutline, height - buttonHeight - buttonOutline, buttonOutline + buttonWidth, height - buttonOutline, "Load",
        []{
            std::cout << "Load" << std::endl;
        }
    ));
	menu -> addButton(new Button(buttonOutline + 1 * buttonWidth, height - buttonHeight - buttonOutline, buttonOutline + 2 * buttonWidth, height - buttonOutline,
			"Save", [this]{
            std::cout << "Save" << std::endl;
            game -> save();
        }
    ));
	menu -> addButton(new Button(buttonOutline + 2 * buttonWidth, height - buttonHeight - buttonOutline, buttonOutline + 3 * buttonWidth, height - buttonOutline,
			"<<", []{
            std::cout << "<<" << std::endl;
        }
    ));
	menu -> addButton(new Button(buttonOutline + 3 * buttonWidth, height - buttonHeight - buttonOutline, buttonOutline + 4 * buttonWidth, height - buttonOutline,
			">>", []{
            std::cout << ">>" << std::endl;
        }
    ));
	menu -> addButton(new Button(buttonOutline + 4 * buttonWidth, height - buttonHeight - buttonOutline, buttonOutline + 5 * buttonWidth, height - buttonOutline,
			"Hint", []{
            std::cout << "Hint" << std::endl;
        }
    ));
	menu -> addButton(new Button(buttonOutline + 5 * buttonWidth, height - buttonHeight - buttonOutline, buttonOutline + 6 * buttonWidth, height - buttonOutline,
			"Option", []{
            std::cout << "Option" << std::endl;
        }
    ));
	menu -> addButton(new Button(buttonOutline + 6 * buttonWidth, height - buttonHeight - buttonOutline, buttonOutline + 7 * buttonWidth, height - buttonOutline,
			"Quit", [this]{
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
