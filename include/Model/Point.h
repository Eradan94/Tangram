/*!
 * \file Point.h
 * \brief Defines a representation of point.
 * \author Biguenet Denis & Gosset Severin
 * \date 22/02/2019
 */

#pragma once
#include <iostream>
#include <cmath>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
#include <cfloat>

#include "../../include/Controller/Preferences.h"

/*! \class Point
 * \brief Representation of point
 *
 * A point is represented by two coordinates x and y.
 * This class is a template, mainly used with int, double, float or short types.
 */
template<class CoordinateType>
class Point {
private :
	CoordinateType x; /*!X coordinate*/
    CoordinateType y; /*!Y coordinate*/

public :
    /*!
     * \brief Base constructor
     * \param x : x coordinate
     * \param y : y coordinate
     *
     * Creates a point with x and y coordinates
     */
    explicit Point(CoordinateType _x = 0, CoordinateType _y = 0);
    /*!
     * \brief Point constructor with mouse click event
     * \param event : SFML MouseButtonEvent event
     *
     * Creates a point with the coordinates of mouse click
     */
    Point(sf::Event::MouseButtonEvent event);
    /*!
     * \brief Point constructor with mouse motion event
     * \param event : SFML MouseMoveEvent event
     *
     * Creates a point with the coordinates of mouse motion
     */
    Point(sf::Event::MouseMoveEvent event);

    /*!
     * \brief Calculate the distance between two points
     * \param otherPoint : the other point
     * \return the distance between this and other
     */
    double distance(const Point& otherPoint) const;
    /*!
     * \brief Calculate if the translated point is inside the window
     * \param translation : a translation got from mouse moves
     *
     * The translation is performed on the current point.
     * If the point is outside the window, the translation is truncated to avoid this.
     */
    void isInsideWindow(Point<CoordinateType>& translation) const;
    /*!
     * \brief Reduce the size of a piece by coefficient
     * \param coeff : the coefficient, more this coefficient is high, more the piece is reduce
     *
     * This method is used to reduce the size of a piece.
     * In facts, the point's coordinate are divided by the coefficient to translate it.
     */
    void reduceSize(int coeff);
    /*!
     * \brief Rotate a point around another point (a center)
     * \param c : the center
     * \param theta : the angle of rotation (in radians)
     *
     * Rotates the point the current point around c, with theta angle.
     */
    Point<CoordinateType> rotate(const Point<CoordinateType>& c, double theta);

    /*!
     * \brief Normalizes points
     * \param points : vector of points
     * \return : a new rotated point
     *
     */
    static void normalize(std::vector<Point<CoordinateType>> & points);

    CoordinateType getX() const;
    CoordinateType getY() const;

    bool operator== (const Point<CoordinateType>& other) const;
    bool operator!= (const Point<CoordinateType>& other) const;
    Point<CoordinateType> operator+ (const Point& other) const;
    Point<CoordinateType> operator- (const Point& other) const;
    Point<CoordinateType> operator/ (const CoordinateType& val) const;
    Point<CoordinateType>& operator+= (const Point<CoordinateType>& other);
    bool operator< (const Point<CoordinateType>& other) const;
    friend std::ostream& operator<< (std::ostream& os, const Point<CoordinateType>& point) {
        os << "(" << point.x << ", " << point.y << ")";
        return os;
    }
};

template<class CoordinateType>
Point<CoordinateType>::Point(CoordinateType _x, CoordinateType _y)
: x(_x), y(_y){
}

template<class CoordinateType>
Point<CoordinateType>::Point(sf::Event::MouseButtonEvent event) : x(event.x), y(event.y) {
}

template<class CoordinateType>
Point<CoordinateType>::Point(sf::Event::MouseMoveEvent event) : x(event.x), y(event.y) {
}

/* Operators
*/

template<class CoordinateType>
bool Point<CoordinateType>::operator==(const Point<CoordinateType>& other) const {
	return (x == other.x && y == other.y);
}

template<>
inline bool Point<double>::operator==(const Point<double>& other) const {
    Preferences& pref = Preferences::getInstance();
    return this->distance(other) <= pref.getTolerance();
}

template<class CoordinateType>
bool Point<CoordinateType>::operator!=(const Point<CoordinateType>& other) const {
    return !(*this == other);
}

template<class CoordinateType>
Point<CoordinateType> Point<CoordinateType>::operator/ (const CoordinateType& val) const {
    return Point<CoordinateType>(x / val, y / val);
}

template<class CoordinateType>
Point<CoordinateType> Point<CoordinateType>::operator+ (const Point<CoordinateType>& other) const {
    return Point<CoordinateType>(x + other.x, y + other.y);
}

template<class CoordinateType>
Point<CoordinateType> Point<CoordinateType>::operator- (const Point<CoordinateType>& other) const {
    return Point<CoordinateType>(x - other.x, y - other.y);
}

template<class CoordinateType>
Point<CoordinateType>& Point<CoordinateType>::operator+= (const Point<CoordinateType>& other) {
    x += other.x;
    y += other.y;
    return *this;
}

template<class CoordinateType>
bool Point<CoordinateType>::operator< (const Point<CoordinateType>& other) const {
    if ( x == other.x ) {
        return y < other.y;
    }
    return x < other.x;
}

/* Getters
*/
template<class CoordinateType>
CoordinateType Point<CoordinateType>::getX() const{
    return x;
}

template<class CoordinateType>
CoordinateType Point<CoordinateType>::getY() const{
    return y;
}

/* Performs a rotation around another point with an angle theta
*/
template<class CoordinateType>
Point<CoordinateType> Point<CoordinateType>::rotate(const Point<CoordinateType>& center, double theta) {
    CoordinateType newx = (cos(theta) * (x - center.x)) - (sin(theta) * (y - center.y)) + center.x;
    CoordinateType newy = (sin(theta) * (x - center.x)) + (cos(theta) * (y - center.y)) + center.y;
    return Point(newx, newy);
}

template<class CoordinateType>
void Point<CoordinateType>::normalize(std::vector<Point<CoordinateType>> & points) {
	double minX = DBL_MAX;
	double minY = DBL_MAX;

	for_each(points.cbegin(), points.cend(), [&minX, &minY](auto & p){
		if (p.x < minX)
			minX = p.x;

		if (p.y < minY)
			minY = p.y;
	});

	for_each(points.begin(), points.end(), [&minX, &minY](auto & p){
		p.x -= minX;
		p.y -= minY;
	});
}

/* Return the distance between two points
*/
template<class CoordinateType>
double Point<CoordinateType>::distance(const Point& otherPoint) const {
    return sqrt((otherPoint.x - x) * (otherPoint.x - x) + (otherPoint.y - y) * (otherPoint.y - y));
}

template<class CoordinateType>
void Point<CoordinateType>::isInsideWindow(Point<CoordinateType>& translation) const {
    Point p = *this + translation;
    Preferences& pref = Preferences::getInstance();
    if(p.y < 0 || p.y > (sf::VideoMode::getDesktopMode().height - pref.getGameButtonHeight())) {
        translation.y = 0;
    }
    if(p.x < 0 || p.x > sf::VideoMode::getDesktopMode().width) {
        translation.x = 0;
    }
}

template<class CoordinateType>
void Point<CoordinateType>::reduceSize(int coeff) {
    x /= coeff;
    y /= coeff;
}

