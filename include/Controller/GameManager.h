/*!
 * \file GameManager.h
 * \brief Manages the game and the interface
 * \author Biguenet Denis & Gosset Severin
 * \date 22/02/2020
 */

#pragma once

#include "../../include/Controller/Game.h"
#include "../../include/Controller/ActionManager.h"

#include <dirent.h>

/*! \class GameManager
 * \brief A gameManager is represented by a game, a menu, a window and an actionManager
 *
 * Manages the game and the interface (such as displaying or actions)
 */
class GameManager {
public:
    /*!
     * \brief Default constructor
     *
     */
	GameManager();

	/*!
     * \brief Draw method
     *
     */
	void draw() const;

	/*!
     * \brief Performs actions and draw the interface until the user wins or quit.
     *
     */
	void play();

	/*!
     * \brief Check the window state
     * \return true if the window is open
     *
     */
	bool isRunning();

	/*!
     * \brief Initializes the game buttons.
     *
     */
	void initMainGameButtons();

	/*!
     * \brief Initializes the main menu buttons.
     *
     */
	void initMainMenuButtons();

	/*!
     * \brief Initializes the create level menu buttons.
     *
     */
	void initCreateLevelButtons();

	/*!
     * \brief Initializes the loading menu buttons.
     *
     */
	void initLoadGameButtons(int loadIndex);

	/*!
	 * \brief Initialize the save game menu buttons
	 */
	void initSaveGameButton();

	/*!
     * \brief Initializes the wins menu buttons.
     *
     */
	void initWinScreenButtons();

private:
    std::shared_ptr<Menu> menu; /*!The current menu, an interface with elements to draw, such as buttons*/
	std::shared_ptr<Game> game; /*!The current game, composed of movable shapes */
	std::unique_ptr<ActionManager> actionManager; /*!Action manager to manage actions performed by the user*/
	std::unique_ptr<sf::RenderWindow> window; /*!Window where the elements are draw*/
};
