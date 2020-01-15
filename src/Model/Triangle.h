/**
 * Project Tangram
 */


#pragma once

#include <SFML/Graphics.hpp>

#include <iostream>
#include <vector>
#include <cfloat>

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

    vector<CoordinateType> calculateBarycentricCoordinates(const Point<CoordinateType>& p) const;
    bool isClicked(const Point<CoordinateType>& p) const;
    Point<CoordinateType> center() const;

    virtual void rotate(const Point<CoordinateType> center, double theta);
    virtual void centralize(const Point<CoordinateType> clickPos, const Point<CoordinateType> relativePos);
    virtual void translate(const Point<CoordinateType>& translation);
	virtual std::vector<Point<CoordinateType>> getPoints() const;
	virtual double distance(Shape<CoordinateType>* shape, std::vector<Point<CoordinateType>>& points) const;

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
vector<CoordinateType> Triangle<CoordinateType>::calculateBarycentricCoordinates(const Point<CoordinateType>& p) const{
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
bool Triangle<CoordinateType>::isClicked(const Point<CoordinateType>& p) const{
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
Point<CoordinateType> Triangle<CoordinateType>::center() const{
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
void Triangle<CoordinateType>::centralize(const Point<CoordinateType> clickPos, const Point<CoordinateType> relativePos) {
	Point<CoordinateType> point = center() - relativePos;
	Point<CoordinateType> translation = clickPos - point;
    translate(translation);
}

/* Translate a triangle
*/
template<class CoordinateType>
void Triangle<CoordinateType>::translate(const Point<CoordinateType>& translation) {
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

template<class CoordinateType>
vector<Point<CoordinateType>> Triangle<CoordinateType>::getPoints() const {
	vector<Point<CoordinateType>> points;
	points.push_back(a);
	points.push_back(b);
	points.push_back(c);

	return points;
}

/* Calculate the distance between a triangle and another shape.
* The distance between two triangles is the shortest distance between two points from each shape
* points represents the couple of points, to get the translation to perform
*/
template<class CoordinateType>
double Triangle<CoordinateType>::distance(Shape<CoordinateType>* shape, std::vector<Point<CoordinateType>>& points) const {
    // First, get the points from each triangle
    vector<Point<CoordinateType>> selectedPiecePoints = this->getPoints();
    vector<Point<CoordinateType>> otherPoints = shape->getPoints();
    double minDist = DBL_MAX;
    double dist;
    // Calculate the distance between each possible couple of points (p1, p2), where p1 is a point of shape and p2 is a point of the current instance
    for(auto& point : selectedPiecePoints) {
        for(auto& otherPoint : otherPoints) {
            dist = point.distance(otherPoint);
            if(dist < minDist) {
                points[0] = point;
                points[1] = otherPoint;
                minDist = dist;
            }
        }
    }
    return minDist;
}


