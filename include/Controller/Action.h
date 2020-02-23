/*!
 * \file Action.h
 * \brief Defines a representation of action
 * \author Biguenet Denis & Gosset Severin
 * \date 22/02/2020
 */

#pragma once

#include <SFML/Graphics.hpp>
#include <map>
#include <math.h>
#include <iostream>
#include <functional>
#include <string>

/*! \interface Action
 * \brief An action is represented by a lambda function, called when the action is performed
 *
 * Action is a functor.
 */
class Action {
public:
    /*!
     * \brief Constructor
     * \param fct : the function called when the action is performed
     *
     */
	Action(const std::function<void (sf::Event)> &fct);

	/*!
     * \brief Default constructor
     *
     */
	Action();

	/*!
     * \brief Operator(), calls the function
     * \param event : the SFML event
     *
     */
	void operator()(sf::Event event);

private:
	std::function<void (sf::Event)> fct; /*!Lambda function called when the action is performed*/
};

