/*!
 * \file ActionManager.h
 * \brief Interface for clickable elements
 * \author Biguenet Denis & Gosset Severin
 * \date 22/02/2020
 */

#pragma once

#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>

#include "../../include/Controller/Game.h"
#include "../../include/Controller/Action.h"

/*! \class ActionManager
 * \brief Interface for clickable elements
 *
 */
class ActionManager {
public:
    /*!
     * \brief Constructor
     * \param game : the current game
     * \param menu : the current menu
     *
     */
	ActionManager(std::shared_ptr<Game> game = nullptr, std::shared_ptr<Menu> menu = nullptr);

	/*!
     * \brief Sets the game
     * \param game : the new game
     *
     */
	void setGame(std::shared_ptr<Game> game);

	/*!
     * \brief Sets the game
     * \param menu : the new menu
     *
     */
	void setMenu(std::shared_ptr<Menu> menu);

	/*!
     * \brief Registers the event and his associated action into the map
     * \param event : the new game
     * \param action : the action associated to the event
     *
     */
	void registerEvent(sf::Event::EventType event, const std::function<void (sf::Event)> action);

	/*!
     * \brief Gets the action to perform
     * \param event : the event performed by the user
     * \return the action associated to the event
     *
     */
	Action & getAction(sf::Event::EventType event);

private:
	std::map<sf::Event::EventType, Action> actions; /*!A map to associate an action to an SFML event*/
	std::shared_ptr<Game> game; /*!The current game*/
	std::shared_ptr<Menu> menu; /*!The current menu*/
};

