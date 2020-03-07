#include <cstring>
#include "../../include/Controller/GameManager.h"

GameManager::~GameManager() {
	delete window;
	delete actionManager;
}

GameManager::GameManager() : menu(Menu::init()), game(std::shared_ptr<Game> (new Game())), actionManager(new ActionManager(game, menu)),
							 window(new sf::RenderWindow(sf::VideoMode::getDesktopMode(), "Tangram")){
}

void GameManager::initMainMenuButtons() {
    const int width = window->getView().getSize().x;
    const int height = window->getView().getSize().y;
    const int buttonCount = 3;
    const int buttonOutline = 5;
    const int buttonBorderGap = 100;
    const int buttonWidth = (width - 2 * buttonOutline) / buttonCount;
    const int menuHeight = (height - buttonBorderGap);
    const int interButtonGap = menuHeight / (buttonCount * 2);
    const int buttonHeight = (menuHeight - buttonCount * interButtonGap) / buttonCount;

	menu -> addButton(std::unique_ptr<Button>(new Button(width / 2 - (buttonWidth / 2), buttonBorderGap, width / 2 + (buttonWidth / 2), buttonBorderGap + buttonHeight, "Play",
        [this]{
            menu->clear();
            initLoadGameButtons(0);
        }
    )));
    menu -> addButton(std::unique_ptr<Button>(new Button(width / 2 - (buttonWidth / 2), buttonBorderGap + interButtonGap + buttonHeight, width / 2 + (buttonWidth / 2), buttonBorderGap + interButtonGap + 2 * buttonHeight, "Create",
        [this]{
            game.reset();
            game = Game::init(nullptr);
			actionManager->setGame(game);
			menu->clear();
            initCreateLevelButtons();
			actionManager->setMenu(menu);
        }
    )));
    menu -> addButton(std::unique_ptr<Button>(new Button(width / 2 - (buttonWidth / 2), buttonBorderGap + 2 * interButtonGap + 2 * buttonHeight, width / 2 + (buttonWidth / 2), buttonBorderGap + 2 * interButtonGap + 3 * buttonHeight, "Quit",
        [this]{
            window->close();
        }
    )));
}

void GameManager::initMainGameButtons() {
    //Here, initialize the main game buttons
    const int width = window->getView().getSize().x;
    const int height = window->getView().getSize().y;
    const int buttonCount = 4;
	const int buttonOutline = 5;
    const int buttonWidth = (width - 2 * buttonOutline) / buttonCount;
    Preferences& pref = Preferences::getInstance();
    const int buttonHeight = (int)pref.getGameButtonHeight();
	menu -> addButton(std::unique_ptr<Button>(new Button(buttonOutline, height - buttonHeight - buttonOutline, buttonOutline + buttonWidth, height - buttonOutline, "Load",
        [this]{
            menu->clear();
            initLoadGameButtons(0);
			actionManager->setMenu(menu);
        }
    )));
	menu -> addButton(std::unique_ptr<Button>(new Button(buttonOutline + 1 * buttonWidth, height - buttonHeight - buttonOutline, buttonOutline + 2 * buttonWidth, height - buttonOutline,
			"Hint", []{
        }
    )));
    menu -> addButton(std::unique_ptr<Button>(new Button(buttonOutline + 2 * buttonWidth, height - buttonHeight - buttonOutline, buttonOutline + 3 * buttonWidth, height - buttonOutline,
			"Menu", [this]{
            game.reset();
            game = std::shared_ptr<Game>(new Game());
			actionManager->setGame(game);
			menu->clear();
			initMainMenuButtons();
			actionManager->setMenu(menu);
        }
    )));
	menu -> addButton(std::unique_ptr<Button>(new Button(buttonOutline + 3 * buttonWidth, height - buttonHeight - buttonOutline, buttonOutline + 4 * buttonWidth, height - buttonOutline,
			"Quit", [this]{
            window->close();
        }
    )));
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
	menu -> addButton(std::unique_ptr<Button>(new Button(200, 100, width - 200, 200, "You won !",
		 []{
		 }
	)));
	menu -> addButton(std::unique_ptr<Button>(new Button(width / 2 - (buttonWidth / 2), buttonBorderGap, width / 2 + (buttonWidth / 2), buttonBorderGap + buttonHeight, "Load",
		 [this]{
			 menu->clear();
			 initLoadGameButtons(0);
			 actionManager->setMenu(menu);
		 }
	)));
	menu -> addButton(std::unique_ptr<Button>(new Button(width / 2 - (buttonWidth / 2), buttonBorderGap + 1 * interButtonGap + 1 * buttonHeight, width / 2 + (buttonWidth / 2), buttonBorderGap + 1 * interButtonGap + 2 * buttonHeight, "Main menu",
		 [this]{
			 game.reset();
			 game = std::shared_ptr<Game>(new Game());
			 actionManager->setGame(game);
			 menu->clear();
			 initMainMenuButtons();
			 actionManager->setMenu(menu);
		 }
	)));
	menu -> addButton(std::unique_ptr<Button>(new Button(width / 2 - (buttonWidth / 2), buttonBorderGap + 2 * interButtonGap + 2 * buttonHeight, width / 2 + (buttonWidth / 2), buttonBorderGap + 2 * interButtonGap + 3 * buttonHeight, "Quit",
		 [this]{
			 window->close();
		 }
	)));
}

void GameManager::initLoadGameButtons(int loadIndex) {
    //Here, initialize the main game buttons
    const int width = window->getView().getSize().x;
    const int height = window->getView().getSize().y;
    const int levelByLoadIndex = 9;

    const int xOffset = 160;
    const int yOffset = 100;
    const int interButtonGap = 50;
    const int levelByLine = sqrt(levelByLoadIndex);
    const int buttonWidth = (width - 2 * xOffset - (levelByLine - 1) * interButtonGap) / levelByLine;
    const int buttonHeight = (height - 2 * yOffset - (levelByLine - 1) * interButtonGap) / levelByLine;

    int i = 0; // Nombre de niveau actuel à afficher sur le menu
    int j = 0; // nombre de niveaux parcourus (à afficher ou non)
    DIR* dpdf = nullptr;
    struct dirent* epdf = nullptr;
    dpdf = opendir("../Tangram/levels/");
    char level[260];
    if (dpdf != nullptr){
        while ((epdf = readdir(dpdf))){
            if(strcmp(epdf->d_name, ".") && strcmp(epdf->d_name, "..")) { // . et .. ne sont pas des niveaux, donc on ne les compte pas
                if(j >= loadIndex * levelByLoadIndex && j < loadIndex * levelByLoadIndex + levelByLoadIndex) {
                    strcpy(level, epdf->d_name);
                    char prefix[300] = "../Tangram/levels/";
                    strcat(prefix, level);
                    std::unique_ptr<Button> button = std::unique_ptr<Button>(new Button(xOffset + (i % levelByLine) * buttonWidth + (i % levelByLine) * interButtonGap,
                                                 yOffset + (i / levelByLine) * buttonHeight + (i / levelByLine) * interButtonGap,
                                                 xOffset + (i % levelByLine) * buttonWidth + (i % levelByLine) * interButtonGap + buttonWidth,
                                                 yOffset + (i / levelByLine) * buttonHeight + (i / levelByLine) * interButtonGap + buttonHeight, "",
                        [this, prefix]{
                            menu->clear();
                            game = Game::init(prefix);
                            actionManager->setGame(game);
                            initMainGameButtons();
                            actionManager->setMenu(menu);
                        }
                    ));
                    std::shared_ptr<Shape<double>> goal = std::shared_ptr<Shape<double>>(Piece<double>::createPiece(prefix));
                    Point<double> buttonCenter = button->center();
                    goal->reduceSize(4);
                    Point<double> pieceCenter = goal->center();
                    Point<double> translation = buttonCenter - pieceCenter;
                    goal->translate(translation);
                    menu->addDecorationPiece(goal);
                    menu -> addButton(std::move(button));
                    i++;
                }
                j++;
            }
        }
    }
    closedir(dpdf);

    if(loadIndex > 0) {
        menu -> addButton(std::unique_ptr<Button>(new Button(40, height / 2 - 35, 110, height / 2 + 35, "<<",
        [this, loadIndex]{
            menu->clear();
            initLoadGameButtons(loadIndex - 1);
        }
        )));
    }
    if(i == levelByLoadIndex) {
    menu -> addButton(std::unique_ptr<Button>(new Button(width - 110, height / 2 - 35, width - 40, height / 2 + 35, ">>",
        [this, loadIndex, i]{
            menu->clear();
            initLoadGameButtons(loadIndex + 1);
        }
        )));
    }

	actionManager->setGame(game);
	actionManager->setMenu(menu);
}

void GameManager::initCreateLevelButtons() {
    //Here, initialize the main game buttons
    const int width = window->getView().getSize().x;
    const int height = window->getView().getSize().y;
    const int buttonCount = 3;
	const int buttonOutline = 5;
    const int buttonWidth = (width - 2 * buttonOutline) / buttonCount;
    const int buttonHeight = 0.1 * height;
	menu -> addButton(std::unique_ptr<Button>(new Button(buttonOutline, height - buttonHeight - buttonOutline, buttonOutline + buttonWidth, height - buttonOutline,
			"Save level", [this]{
            menu->clear();
            initSaveGameButton();
        }
    )));
    menu -> addButton(std::unique_ptr<Button>(new Button(buttonOutline + 1 * buttonWidth, height - buttonHeight - buttonOutline, buttonOutline + 2 * buttonWidth, height - buttonOutline,
			"Menu", [this]{
            game.reset();
            game = std::shared_ptr<Game>(new Game());
			actionManager->setGame(game);
			menu->clear();
			initMainMenuButtons();
			actionManager->setMenu(menu);
        }
    )));
	menu -> addButton(std::unique_ptr<Button>(new Button(buttonOutline + 2 * buttonWidth, height - buttonHeight - buttonOutline, buttonOutline + 3 * buttonWidth, height - buttonOutline,
			"Quit", [this]{
            window->close();
        }
    )));
}

void GameManager::initSaveGameButton() {
    const int width = window->getView().getSize().x;
    const int height = window->getView().getSize().y;
	const int buttonOutline = 5;
    const int buttonHeight = 0.1 * height;
    menu -> setInputBox(std::unique_ptr<Button>(new Button(buttonOutline, height - buttonHeight - buttonOutline, width / 2 + buttonOutline, height - buttonOutline,
        "Level name : ", [this]{

        }
    )));
    menu -> addButton(std::unique_ptr<Button>(new Button(width / 2 + buttonOutline * 2, height - buttonHeight - buttonOutline, 0.75 * width + 2 * buttonOutline, height - buttonOutline,
        "Save", [this]{
            game -> save(menu->getInputBoxText());
            game.reset();
            game = std::shared_ptr<Game>(new Game());
			actionManager->setGame(game);
			menu->clear();
			initMainMenuButtons();
			actionManager->setMenu(menu);
        }
    )));
    menu -> addButton(std::unique_ptr<Button>(new Button(0.75 * width + 2 * buttonOutline, height - buttonHeight - buttonOutline, width - buttonOutline, height - buttonOutline,
        "Cancel", [this]{
            menu->clear();
            initCreateLevelButtons();
        }
    )));
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
	}
	if(game->getGameState()) {
        game = std::shared_ptr<Game>(new Game());
        actionManager->setGame(game);
        menu->clear();
        initWinScreenButtons();
    }
	draw();
}

bool GameManager::isRunning() {
	return window -> isOpen();
}
