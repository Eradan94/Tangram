/*!
 * \file GameBuilder.h
 * \brief Game builder class
 * \author Biguenet Denis & Gosset Severin
 * \date 22/02/2020
 */

#pragma once

#include "../../include/Model/Shape.h"
#include "../../include/View/Button.h"
#include "../../include/Controller/Game.h"

/*! \class GameBuilder
 * \brief Game builder class
 *
 */
class GameBuilder {
public:
    /*!
     * \brief Default constructor
     *
     */
	GameBuilder();

	/*!
     * \brief Adds a shape into the game
     * \param shape : the shape added into the game
     *
     */
	void withShape(std::shared_ptr<Shape<double>> shape);

	/*!
     * \brief Build function
     * \param fileName : the function called when the action is performed
     *
     */
	std::shared_ptr<Game> build(const char * fileName);
	//std::shared_ptr<Game> build();

private:
	std::vector<std::shared_ptr<Shape<double>>> pieces; /*!vector of pieces, the pieces used by the user to reproduce the shape*/
};

