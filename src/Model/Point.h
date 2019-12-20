/**
 * Project Tangram
 */


#ifndef _POINT_H
#define _POINT_H

#include <iostream>
#include <math.h>

template<class CoordinateType>
class Point {
private :
    CoordinateType x;
    CoordinateType y;

public :
    Point(CoordinateType _x = 0, CoordinateType _y = 0);
    bool operator== (const Point& other) const;
    bool operator!= (const Point& other) const;
    Point<CoordinateType> operator+ (const Point& other) const;
    Point<CoordinateType> operator- (const Point& other) const;
    //Point<CoordinateType> operator- () const;
    Point<CoordinateType> operator/ (const CoordinateType& val) const;
    Point<CoordinateType>& operator+= (const Point& other);
    //Point<CoordinateType>& operator-= (const Point& other);

    CoordinateType getX();
    CoordinateType getY();

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

/*template<class CoordinateType>
Point<CoordinateType> Point<CoordinateType>::operator- () const {
    return Point<CoordinateType>(-x, -y);
}*/

/*template<class CoordinateType>
Point<CoordinateType>& Point<CoordinateType>::operator-= (const Point<CoordinateType>& other) {
    x -= other.x;
    y -= other.y;
    return *this;
}*/

/* Getters
*/
template<class CoordinateType>
CoordinateType Point<CoordinateType>::getX() {
    return x;
}

template<class CoordinateType>
CoordinateType Point<CoordinateType>::getY() {
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

#endif //_POINT_H
