/**
 * Project Tangram
 */


#pragma once
#include <iostream>
#include <cmath>
#include <SFML/Window/Event.hpp>

template<class CoordinateType>
class Point {
private :
	CoordinateType x;
    CoordinateType y;

public :
    explicit Point(CoordinateType _x = 0, CoordinateType _y = 0);
    Point(sf::Event::MouseButtonEvent event);
    Point(sf::Event::MouseMoveEvent event);
    bool operator== (const Point& other) const;
    bool operator!= (const Point& other) const;
    Point<CoordinateType> operator+ (const Point& other) const;
    Point<CoordinateType> operator- (const Point& other) const;
    Point<CoordinateType> operator/ (const CoordinateType& val) const;
    Point<CoordinateType>& operator+= (const Point& other);
    double distance(const Point& otherPoint);

    CoordinateType getX() const;
    CoordinateType getY() const;

    void rotate(const Point<CoordinateType>& c, double theta);

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
void Point<CoordinateType>::rotate(const Point<CoordinateType>& center, double theta) {
    CoordinateType newx = (cos(theta) * (x - center.x)) - (sin(theta) * (y - center.y)) + center.x;
    CoordinateType newy = (sin(theta) * (x - center.x)) + (cos(theta) * (y - center.y)) + center.y;
    x = newx;
    y = newy;
}

/* Return the distance between two points
*/
template<class CoordinateType>
double Point<CoordinateType>::distance(const Point& otherPoint) {
    return sqrt((otherPoint.x - x) * (otherPoint.x - x) + (otherPoint.y - y) * (otherPoint.y - y));
}

