#include <cstring>
#include "../../include/Controller/GameManager.h"

GameManager::~GameManager() {
	delete game;
	delete menu;
	delete window;
	delete actionManager;
}

GameManager::GameManager() : menu(Menu::init()), game(new Game()), actionManager(new ActionManager(game, menu)),
							 window(new sf::RenderWindow(sf::VideoMode::getDesktopMode(), "Tangram")){
}

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
            menu->clear();
            initLoadGameButtons();
        }
    ));
    menu -> addButton(new Button(width / 2 - (buttonWidth / 2), buttonBorderGap + interButtonGap + buttonHeight, width / 2 + (buttonWidth / 2), buttonBorderGap + interButtonGap + 2 * buttonHeight, "Create",
        [this]{
            std::cout << "Create level" << std::endl;
            delete game;
            game = Game::init();
			actionManager->setGame(game);
            menu->clear();
            initCreateLevelButtons();
			actionManager->setMenu(menu);
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
    const int buttonCount = 7;
	const int buttonOutline = 5;
    const int buttonWidth = (width - 2 * buttonOutline) / buttonCount;
    const int buttonHeight = 0.1 * height;
	menu -> addButton(new Button(buttonOutline, height - buttonHeight - buttonOutline, buttonOutline + buttonWidth, height - buttonOutline, "Load",
        [this]{
            std::cout << "Load" << std::endl;
            menu->clear();
            initLoadGameButtons();
			actionManager->setMenu(menu);
        }
    ));
	menu -> addButton(new Button(buttonOutline + 1 * buttonWidth, height - buttonHeight - buttonOutline, buttonOutline + 2 * buttonWidth, height - buttonOutline,
			"Hint", []{
            std::cout << "Hint" << std::endl;
        }
    ));
	menu -> addButton(new Button(buttonOutline + 2 * buttonWidth, height - buttonHeight - buttonOutline, buttonOutline + 3 * buttonWidth, height - buttonOutline,
			"Options", []{
            std::cout << "Options" << std::endl;
        }
    ));
    menu -> addButton(new Button(buttonOutline + 3 * buttonWidth, height - buttonHeight - buttonOutline, buttonOutline + 4 * buttonWidth, height - buttonOutline,
			"Menu", [this]{
            std::cout << "Menu" << std::endl;
            delete game;
            game = new Game();
			actionManager->setGame(game);
			menu->clear();
			initMainMenuButtons();
			actionManager->setMenu(menu);
        }
    ));
	menu -> addButton(new Button(buttonOutline + 4 * buttonWidth, height - buttonHeight - buttonOutline, buttonOutline + 5 * buttonWidth, height - buttonOutline,
			"Quit", [this]{
            std::cout << "Quit" << std::endl;
            window->close();
        }
    ));
}

void GameManager::initWinScreenButtons() {
	const int width = window->getView().getSize().x;
	const int height = window->getView().getSize().y;
	const int buttonCount = 3;
	const int buttonOutline = 5;
	const int buttonBorderGap = 300;
	const int buttonWidth = (width - 2 * buttonOutline) / buttonCount;
	const int menuHeight = (height - buttonBorderGap);
	const int interButtonGap = menuHeight / (buttonCount * 2);
	const int buttonHeight = (menuHeight - buttonCount * interButtonGap) / buttonCount;
	//Bouton sans action, a remplacer par autre chose de plus adapte
	menu -> addButton(new Button(200, 100, width - 200, 200, "You won !",
		 []{
		 }
	));
	menu -> addButton(new Button(width / 2 - (buttonWidth / 2), buttonBorderGap, width / 2 + (buttonWidth / 2), buttonBorderGap + buttonHeight, "Load",
		 [this]{
			 std::cout << "Load" << std::endl;
			 menu->clear();
			 initLoadGameButtons();
			 actionManager->setMenu(menu);
		 }
	));
	menu -> addButton(new Button(width / 2 - (buttonWidth / 2), buttonBorderGap + 1 * interButtonGap + 1 * buttonHeight, width / 2 + (buttonWidth / 2), buttonBorderGap + 1 * interButtonGap + 2 * buttonHeight, "Main menu",
		 [this]{
			 std::cout << "Main menu" << std::endl;
			 delete game;
			 game = new Game();
			 actionManager->setGame(game);
			 menu->clear();
			 initMainMenuButtons();
			 actionManager->setMenu(menu);
		 }
	));
	menu -> addButton(new Button(width / 2 - (buttonWidth / 2), buttonBorderGap + 2 * interButtonGap + 2 * buttonHeight, width / 2 + (buttonWidth / 2), buttonBorderGap + 2 * interButtonGap + 3 * buttonHeight, "Quit",
		 [this]{
			 std::cout << "Quit" << std::endl;
			 window->close();
		 }
	));
}

void GameManager::initLoadGameButtons() {
    //Here, initialize the main game buttons
    const int width = window->getView().getSize().x;
    const int buttonWidth = 250;
    const int buttonHeight = 60;

    int i = 0;
    DIR *dpdf;
    struct dirent *epdf;
    dpdf = opendir("../Tangram/levels/");
    char level[260];
    if (dpdf != NULL){
        while ((epdf = readdir(dpdf))){
            if(strcmp(epdf->d_name, ".") && strcmp(epdf->d_name, "..")) {
                strcpy(level, epdf->d_name);
                menu -> addButton(new Button(width / 2 - (buttonWidth / 2), (i + 1) * buttonHeight, width / 2 + (buttonWidth / 2), (i + 2) * buttonHeight, epdf->d_name,
                    [this, level]{
                        char prefix[300] = "../Tangram/levels/";
                        strcat(prefix, level);
                        menu->clear();
                        game = Game::init(prefix);
						actionManager->setGame(game);
						initMainGameButtons();
						actionManager->setMenu(menu);
                    }
                ));
				i++;
            }
        }
    }
    closedir(dpdf);
	actionManager->setGame(game);
	actionManager->setMenu(menu);
}

void GameManager::initCreateLevelButtons() {
    //Here, initialize the main game buttons
    const int width = window->getView().getSize().x;
    const int height = window->getView().getSize().y;
    const int buttonCount = 4;
	const int buttonOutline = 5;
    const int buttonWidth = (width - 2 * buttonOutline) / buttonCount;
    const int buttonHeight = 0.1 * height;
	menu -> addButton(new Button(buttonOutline, height - buttonHeight - buttonOutline, buttonOutline + buttonWidth, height - buttonOutline,
			"Save level", [this]{
            std::cout << "Save level" << std::endl;
            game -> save();
        }
    ));
	menu -> addButton(new Button(buttonOutline + 1 * buttonWidth, height - buttonHeight - buttonOutline, buttonOutline + 2 * buttonWidth, height - buttonOutline,
			"Options", []{
            std::cout << "Options" << std::endl;
        }
    ));
    menu -> addButton(new Button(buttonOutline + 2 * buttonWidth, height - buttonHeight - buttonOutline, buttonOutline + 3 * buttonWidth, height - buttonOutline,
			"Menu", [this]{
            std::cout << "Menu" << std::endl;
            delete game;
            game = new Game();
			actionManager->setGame(game);
			menu->clear();
			initMainMenuButtons();
			actionManager->setMenu(menu);
        }
    ));
	menu -> addButton(new Button(buttonOutline + 3 * buttonWidth, height - buttonHeight - buttonOutline, buttonOutline + 4 * buttonWidth, height - buttonOutline,
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
	while (window -> pollEvent(event)) {
		if (event.type == sf::Event::Closed)
			window -> close();
		Action act = actionManager -> getAction(event.type);
		act(event);
		if(game->getGameState()) {
            delete game;
            game = new Game();
            actionManager->setGame(game);
            menu->clear();
            initWinScreenButtons();
		}
	}
	draw();
}

bool GameManager::isRunning() {
	return window -> isOpen();
}
