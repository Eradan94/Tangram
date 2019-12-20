/**
 * Project Tangram
 */


#ifndef _POINT_H
#define _POINT_H

#include <iostream>
#include <vector>

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
    Point<CoordinateType> operator/ (const CoordinateType& val) const;
    Point<CoordinateType>& operator+= (const Point& other);

    CoordinateType getX();
    CoordinateType getY();

    std::vector<CoordinateType> createVector(const Point& other);

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
Point<CoordinateType>& Point<CoordinateType>::operator+= (const Point<CoordinateType>& other) {
    x += other.x;
    y += other.y;
    return *this;
}

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

/* Create a vector from two points
*/
template<class CoordinateType>
vector<CoordinateType> Point<CoordinateType>::createVector(const Point& other) {
	vector<CoordinateType> v;
	v.push_back(other.x - x);
	v.push_back(other.y - y);
	return v;
}

#endif //_POINT_H
