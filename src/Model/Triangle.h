/**
 * Project Tangram
 */


#pragma once

#include <SFML/Graphics.hpp>

#include <iostream>
#include <vector>

#include "Point.h"
#include "Shape.h"

template<class CoordinateType>
class Triangle: public Shape<CoordinateType> {
private :
    Point<CoordinateType> a;
    Point<CoordinateType> b;
    Point<CoordinateType> c;
    sf::Color color;

public :
    Triangle(Point<CoordinateType> _a, Point<CoordinateType> _b, Point<CoordinateType> _c, sf::Color color);

    vector<CoordinateType> calculateBarycentricCoordinates(Point<CoordinateType>& p) const;
    bool isInTriangle(Point<CoordinateType>& p) const;
    Point<CoordinateType> center();

    virtual void rotate(Point<CoordinateType> center, double theta);
    virtual void centralize(Point<CoordinateType> clickPos);
    virtual void translate(Point<CoordinateType> translation);

    void draw(sf::RenderWindow& window);

    // friends functions
    friend std::ostream& operator<< (std::ostream& os, const Triangle<CoordinateType>& triangle) {
        os << "Triangle : " << std::endl << "   Point A : " << triangle.a << std::endl << "   Point B : " << triangle.b << std::endl << "   Point C : " << triangle.c;
        return os;
    }
};

template<class CoordinateType>
Triangle<CoordinateType>::Triangle(Point<CoordinateType> _a, Point<CoordinateType> _b, Point<CoordinateType> _c, sf::Color color)
: a(_a), b(_b), c(_c), color(color){
}

/* Calculate the barycentric coordinates of the point
*/
template<class CoordinateType>
vector<CoordinateType> Triangle<CoordinateType>::calculateBarycentricCoordinates(Point<CoordinateType>& p) const{
	vector<CoordinateType> barCoordinates;
	Point<CoordinateType> pa = p - a;
    Point<CoordinateType> pb = p - b;
	Point<CoordinateType> pc = p - c;
	barCoordinates.push_back((pb.getX() * pc.getY()) - (pb.getY() * pc.getX()));
	barCoordinates.push_back((pc.getX() * pa.getY()) - (pc.getY() * pa.getX()));
	barCoordinates.push_back((pa.getX() * pb.getY()) - (pa.getY() * pb.getX()));
	return barCoordinates;
}

/* A point is inside a triangle if all his coordinates are positive or negative
*/
template<class CoordinateType>
bool Triangle<CoordinateType>::isInTriangle(Point<CoordinateType>& p) const{
	std::vector<CoordinateType> barCoordinates = this->calculateBarycentricCoordinates(p);
	if(barCoordinates[0] <= 0 && barCoordinates[1] <= 0 && barCoordinates[2] <= 0)
		return true;
	else if(barCoordinates[0] >= 0 && barCoordinates[1] >= 0 && barCoordinates[2] >= 0)
		return true;
	return false;
}

/* Calculate the triangle's center
*/
template<class CoordinateType>
Point<CoordinateType> Triangle<CoordinateType>::center() {
    return Point<CoordinateType>((a.getX() + b.getX()+ c.getX()) / 3, (a.getY() + b.getY() + c.getY()) / 3);
}

/* Performs a rotation around another point with an angle theta
*/
template<class CoordinateType>
void Triangle<CoordinateType>::rotate(const Point<CoordinateType> center, double theta) {
    a.rotate(center, theta);
    b.rotate(center, theta);
    c.rotate(center, theta);
}

/* Centralize the triangle around the click position
*/
template<class CoordinateType>
void Triangle<CoordinateType>::centralize(Point<CoordinateType> clickPos) {
    Point<CoordinateType> center = center();
    Point<CoordinateType> translation = clickPos - center;
    translate(translation);
}

/* Translate a triangle
*/
template<class CoordinateType>
void Triangle<CoordinateType>::translate(Point<CoordinateType> translation) {
    a += translation;
    b += translation;
    c += translation;
}

/* draw the triangle
*/
template<class CoordinateType>
void Triangle<CoordinateType>::draw(sf::RenderWindow& window) {
    sf::ConvexShape triangle;
    triangle.setPointCount(3);

    // define points
    triangle.setPoint(0, sf::Vector2f(a.getX(), a.getY()));
    triangle.setPoint(1, sf::Vector2f(b.getX(), b.getY()));
    triangle.setPoint(2, sf::Vector2f(c.getX(), c.getY()));

    triangle.setFillColor(color);
    window.draw(triangle);
}

