/*!
 * \file Menu.h
 * \brief Defines a representation of menu.
 * \author Biguenet Denis & Gosset Severin
 * \date 22/02/2020
 */

#pragma once
#include "../../include/View/Drawable.h"
#include "../../include/View/Button.h"
#include "../../include/Model/Shape.h"
#include "../../include/Model/Piece.h"

#include <list>
#include <memory>

/*! \class Menu
 * \brief Representation of menu
 *
 * A menu is represented by a vector of buttons and a vector of pieces (decorations)
 */
class Menu: public Drawable {
public :
    /*!
     * \brief default constructor
     *
     */
	Menu();

	/*!
     * \brief menu initialization
     * \return a pointer to the new menu
     *
     */
	static std::shared_ptr<Menu> init();

	/*!
     * \brief Adds a button in the menu's vector of buttons
     * \param button : the button added into the vector
     *
     */
	void addButton(std::unique_ptr<Button> button);

	/*!
	 * \brief Sets an input button for the menu
	 * \param inputBox the button to sets as input
	 */
	void setInputBox(std::unique_ptr<Button> inputBox);

	/*!
     * \brief Draw method
     * \param window : the window chre the button is draw
     *
     */
	void draw(sf::RenderWindow & window);

	/*!
     * \brief Checks if a button is clicked by the user
     * \param event : a point (position of the mouse cursor the the user clicked)
     *
     */
	void select(const Point<double> & event);

	/*!
     * \brief Clears the vectors
     *
     */
	void clear();

	/*!
     * \brief Adds a shape in the menu's vector of decoration shapes
     * \param piece : the piece added into the vector
     *
     */
	void addDecorationPiece(std::shared_ptr<Shape<double>> piece);

	/*!
	 * \brief Adds a character to the input button of the menu, if it exists
	 * \param c the character to add
	 */
	void setText(char c);

	/*!
	 * \brief Returns the input text of the input button
	 * \return the input text
	 */
	std::string getInputBoxText();

private :
    std::vector<std::unique_ptr<Button>> buttons; /*!Vector of buttons */
    std::shared_ptr<Button> inputBox; /*!Input box*/
    std::vector<std::shared_ptr<Shape<double>>> decorationPieces; /*!Vector of decoration pieces */
};

