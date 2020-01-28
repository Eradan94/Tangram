#include "GameManager.h"
#include "Action.h"

GameManager::~GameManager() {
	delete game;
	delete menu;
	delete window;
}

GameManager::GameManager() : menu(Menu::init()),
	window(new sf::RenderWindow(sf::VideoMode::getDesktopMode(), "Tangram")){
    game = new Game();
	Action::initActions(*game, *menu);
}

/*GameManager::GameManager(const char *filename) : game(Game::init(filename)), menu(Menu::init()),
	window(new sf::RenderWindow(sf::VideoMode::getDesktopMode(), "Tangram")){
	Action::initActions(*game, *menu);
}*/

void GameManager::initMainMenuButtons() {
    //Here, initialize the main menu buttons
    const int width = window->getView().getSize().x;
    const int height = window->getView().getSize().y;
    const int buttonCount = 4;
    const int buttonOutline = 5;
    const int buttonBorderGap = 100;
    const int buttonWidth = (width - 2 * buttonOutline) / buttonCount;
    const int menuHeight = (height - buttonBorderGap);
    const int interButtonGap = menuHeight / (buttonCount * 2);
    const int buttonHeight = (menuHeight - buttonCount * interButtonGap) / buttonCount;
	menu -> addButton(new Button(width / 2 - (buttonWidth / 2), buttonBorderGap, width / 2 + (buttonWidth / 2), buttonBorderGap + buttonHeight, "Load",
        [this]{
            std::cout << "Load" << std::endl;
            game = Game::init("../Tangram/levels/7.txt");
            menu->clear();
            //delete menu; // BUG
            //menu = Menu::init(); // BUG
            initMainGameButtons();
            Action::initActions(*game, *menu);
        }
    ));
    menu -> addButton(new Button(width / 2 - (buttonWidth / 2), buttonBorderGap + interButtonGap + buttonHeight, width / 2 + (buttonWidth / 2), buttonBorderGap + interButtonGap + 2 * buttonHeight, "Create",
        []{
            std::cout << "Create level" << std::endl;
        }
    ));
    menu -> addButton(new Button(width / 2 - (buttonWidth / 2), buttonBorderGap + 2 * interButtonGap + 2 * buttonHeight, width / 2 + (buttonWidth / 2), buttonBorderGap + 2 * interButtonGap + 3 * buttonHeight, "Options",
        []{
            std::cout << "Options" << std::endl;
        }
    ));
    menu -> addButton(new Button(width / 2 - (buttonWidth / 2), buttonBorderGap + 3 * interButtonGap + 3 * buttonHeight, width / 2 + (buttonWidth / 2), buttonBorderGap + 3 * interButtonGap + 4 * buttonHeight, "Quit",
        [this]{
            std::cout << "Quit" << std::endl;
            window->close();
        }
    ));

}

void GameManager::initMainGameButtons() {
    //Here, initialize the main game buttons
    const int width = window->getView().getSize().x;
    const int height = window->getView().getSize().y;
    const int buttonCount = 8;
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
			"Options", []{
            std::cout << "Options" << std::endl;
        }
    ));
    menu -> addButton(new Button(buttonOutline + 6 * buttonWidth, height - buttonHeight - buttonOutline, buttonOutline + 7 * buttonWidth, height - buttonOutline,
			"Menu", [this]{
            std::cout << "Menu" << std::endl;
            delete game;
            game = new Game();
            menu->clear();
            initMainMenuButtons();
            Action::initActions(*game, *menu);
        }
    ));
	menu -> addButton(new Button(buttonOutline + 7 * buttonWidth, height - buttonHeight - buttonOutline, buttonOutline + 8 * buttonWidth, height - buttonOutline,
			"Quit", [this]{
            std::cout << "Quit" << std::endl;
            window->close();
        }
    ));
    //std::cout << " e : " << *menu << std::endl;
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
