/*!
 * \file Game.h
 * \brief Defines a representation of game
 * \author Biguenet Denis & Gosset Severin
 * \date 22/02/2020
 */

#pragma once

#include "../../include/View/Drawable.h"
#include "../../include/View/Button.h"
#include "../../include/Model/Shape.h"
#include "../../include/Model/Piece.h"
#include "../../include/View/Menu.h"

#include <list>
#include <vector>
#include <cfloat>
#include <memory>

/*! \class Game
 * \brief A game is represented by movable pieces and a shape to reproduce
 *
 */
class Game {
public :
    /*!
     * \brief Initialize a game from a file
     * \param filename : the name of the file
     * \return a pointer to the new game
     *
     */
	static std::shared_ptr<Game> init(const char * filename);

	/*!
     * \brief Constructor, create a new game from a vector of pieces and a goal
     * \param pieces : the vector of pieces, used by the user to reproduce the shape
     * \param goal : the shape to reproduce
     */
	Game(std::vector<std::shared_ptr<Shape<double>>> pieces, std::unique_ptr<Piece<double>> goal);

	/*!
     * \brief Default constructor
     *
     */
	Game();

	/*!
     * \brief Destructor
     *
     */
	~Game();

	/*!
     * \brief Draw method
     * \param window : window where the game is draw
     *
     */
	void draw(sf::RenderWindow & window);

	/*!
     * \brief Selects a piece
     * \param event : position of the mouse click
     *
     * Checks if a piece is selected by checking if the point is inside a it.
     */
	void select(const Point<double> & event);

	/*!
     * \brief Deselects the selected piece
     *
     */
	void deselect();

	/*
	*!!!!!!!!!!
	* TODO
	*!!!!!!!!!!
	*/
	void centralizeSelected(const sf::Event::MouseMoveEvent event);

	/*!
     * \brief Rotates the selected piece
     * \param d : rotation angle
     *
     */
	void rotateSelected(const double d);

	/*
	*!!!!!!!!!!
	* TODO
	*!!!!!!!!!!
	*/
	void save();

	/*!
     * \brief Magnetizes the selected piece when released
     *
     * The piece is magnetized by the closest vertex of another shape.
     * The reach of magnetism is defined in Preferences class
     */
	void magnetize();

	/*!
     * \brief Checks if the goal is reproduced
     *
     * If the goal is reproduced by the user, a win screen appears.
     */
	void validateShape();

	/*!
     * \brief Gets the game state
     * \return the game state
     *
     */
	bool getGameState();

private :
	std::vector<std::shared_ptr<Shape<double>>> pieces; /*!Vector of movable and clickable pieces*/
	std::shared_ptr<Shape<double>> selected; /*!The selected piece*/
	std::unique_ptr<Piece<double>> goal; /*!The shape to reproduce*/
	Point<double> relativePos; /* TODO*/
	bool gameState; /*!Game state*/

	// All shapes
	// little triangles
	static constexpr double littleTriangle1[2 * 3 * 2] = {
			100., 300., 100., 400., 000., 400.,
			100., 300., 200., 400., 100., 400.
	};
	static constexpr double littleTriangle2[2 * 3 * 2] = {
			200., 200., 300., 100., 300., 200.,
			200., 200., 300., 200., 300., 300.
	};

	// medium triangle
	static constexpr double mediumTriangle[2 * 3 * 4] = {
			300., 300., 300., 400., 200., 400.,
			300., 300., 400., 400., 300., 400.,
			300., 300., 400., 300., 400., 400.,
			300., 300., 400., 200., 400., 300.
	};

	// large triangle
	static constexpr double largeTriangle1[2 * 3 * 8] = {
			100., 100., 000., 000., 100., 000.,
			100., 100., 100., 000., 200., 000.,
			100., 100., 200., 000., 200., 100.,
			100., 100., 200., 100., 200., 200.,
			300., 100., 200., 200., 200., 100.,
			300., 100., 200., 100., 200., 000.,
			300., 100., 200., 000., 300., 000.,
			300., 100., 300., 000., 400., 000.
	};
	static constexpr double largeTriangle2[2 * 3 * 8] = {
			100., 100., 000., 000., 000., 100.,
			100., 100., 000., 100., 000., 200.,
			100., 100., 000., 200., 100., 200.,
			100., 100., 100., 200., 200., 200.,
			100., 300., 200., 200., 100., 200.,
			100., 300., 100., 200., 000., 200.,
			100., 300., 000., 200., 000., 300.,
			100., 300., 000., 300., 000., 400.
	};

	// square
	static constexpr double square[2 * 3 * 4] = {
			200., 300., 100., 300., 200., 200.,
			200., 300., 200., 200., 300., 300.,
			200., 300., 300., 300., 200., 400.,
			200., 300., 200., 400., 100., 300.
	};

	// parallelogram
	static constexpr double parallelogram[2 * 3 * 4] = {
			300., 100., 400., 000., 400., 100.,
			300., 100., 400., 100., 400., 200.,
			400., 200., 300., 100., 300., 200.,
			400., 200., 300., 200., 300., 300.
	};
};
