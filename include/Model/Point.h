/**
 * Project Tangram
 */


#pragma once
#include <iostream>
#include <cmath>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
#include <cfloat>

#include "../../include/Controller/Preferences.h"

template<class CoordinateType>
class Point {
private :
	CoordinateType x;
    CoordinateType y;

public :
    explicit Point(CoordinateType _x = 0, CoordinateType _y = 0);
    Point(sf::Event::MouseButtonEvent event);
    Point(sf::Event::MouseMoveEvent event);
    bool operator== (const Point<CoordinateType>& other) const;
    bool operator!= (const Point<CoordinateType>& other) const;
    Point<CoordinateType> operator+ (const Point& other) const;
    Point<CoordinateType> operator- (const Point& other) const;
    Point<CoordinateType> operator/ (const CoordinateType& val) const;
    Point<CoordinateType>& operator+= (const Point<CoordinateType>& other);
    bool operator< (const Point<CoordinateType>& other) const;
    double distance(const Point& otherPoint) const;
    void isInsideWindow(Point<CoordinateType>& translation) const;
    void reduceSize(int coeff);

    static void normalize(std::vector<Point<CoordinateType>> & points);

    CoordinateType getX() const;
    CoordinateType getY() const;

    Point<CoordinateType> rotate(const Point<CoordinateType>& c, double theta);

    // friends functions
    friend std::ostream& operator<< (std::ostream& os, const Point<CoordinateType>& point) {
        os << "(" << point.x << ", " << point.y << ")";
        return os;
    }
};

using namespace std;

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
void Point<CoordinateType>::normalize(vector<Point<CoordinateType>> & points) {
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

