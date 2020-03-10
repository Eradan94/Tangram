/*!
 * \file Button.h
 * \brief Defines a representation of buttons.
 * \author Biguenet Denis & Gosset Severin
 * \date 22/02/2020
 */


#pragma once
#include <SFML/Graphics.hpp>
#include <functional>
#include <memory>

#include "../../include/View/Drawable.h"
#include "../../include/Controller/Clickable.h"
#include "../../include/Model/Point.h"

/*! \class Button
 * \brief Representation of button
 *
 * A button is represented by two points (top left point and bottom right point), a text, a lambda function called when the button is selected and sfml rectangle and text.
 */
class Button: public Drawable, public Clickable<double> {
public :
    /*!
     * \brief default constructor
     * \param topLeftX : X coordinate of top left point
     * \param topLeftY : Y coordinate of top left point
     * \param bottomRightX : X coordinate of bottom right point
     * \param bottomRightY : Y coordinate of bottom right point
     * \param text : string that contains the button's text
     * \param _fct : lambda function called when the button is clicked
     *
     */
    Button(int topLeftX, int topLeftY, int bottomRightX, int bottomRightY, std::string text, std::function<void()> _fct);

    /*!
     * \brief destructor to delete txt field's font
     *
     */
    ~Button();

    /*!
     * \brief Calls the lambda function of the button
     *
     */
    void callFct();

    /*!
     * \brief Draw method
     * \param window : window where the button is draw
     *
     */
    void draw(sf::RenderWindow& window) override;

    /*!
     * \brief Check if the button is clicked by the user
     * \param p : the position of the click
     * \return true if the button is clicked, false in the other case
     *
     */
    bool isClicked(const Point<double>& p) const override;

    /*!
     * \brief Gets the center of the button
     * \return the center of the button
     *
     */
    Point<double> center() const;

    void setText(char input);

    std::string getInputText();

private :
    Point<double> topLeft; /*!Top left point*/
    Point<double> bottomRight; /*!Right bottom point*/
    std::string text; /*!Button's text*/
    std::string inputText;
	std::function<void ()> fct; /*!Lambda function called when the button is clicked*/
	std::unique_ptr<sf::RectangleShape> rectangle; /*!SFML rectangle to draw the button*/
	std::unique_ptr<sf::Text> txt; /*!SFML text to draw the button's content*/
};
