/*!
 * \file Clickable.h
 * \brief Interface for clickable elements
 * \author Biguenet Denis & Gosset Severin
 * \date 22/02/2020
 */

#pragma once

#include "../../include/Model/Point.h"

/*! \interface Clickable
 * \brief Interface for clickable elements
 *
 */
template<class CoordinateType>
class Clickable {
    /*!
     * \brief Check if the element is clicked by the user
     * \param p : the position of the click
     * \return true if the element is clicked, false in the other case
     *
     */
	virtual bool isClicked(const Point<CoordinateType>& p) const = 0;
};

