/*!
 * \file Triangle.h
 * \brief Defines a representation of triangle.
 * \author Biguenet Denis & Gosset Severin
 * \date 22/02/2020
 */

#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <cfloat>

#include "../../include/Model/Point.h"
#include "../../include/Model/Shape.h"

/*! \class Triangle
 * \brief Representation of triangle
 *
 * A triangle is represented by three points.
 * This class is a template, mainly used with int, double, float or short types.
 */
template<class CoordinateType>
class Triangle: public Shape<CoordinateType> {
private :
    Point<CoordinateType> a; /*!A vertex*/
    Point<CoordinateType> b; /*!B vertex*/
    Point<CoordinateType> c; /*!C vertex*/
    double theta; /*!rotation angle : the triangle is rotated with this*/
    Point<CoordinateType> unrotatedA; /*!A vertex position without rotation*/
    Point<CoordinateType> unrotatedB; /*!B vertex position without rotation*/
    Point<CoordinateType> unrotatedC; /*!C vertex position without rotation*/
    sf::Color color; /*!Triangle color*/

public :
    /*!
     * \brief Base constructor
     * \param _a : first triangle's vertex
     * \param _b : second triangle's vertex
     * \param _c : third triangle's vertex
     * \param color : triangle's color
     *
     * Creates a triangle from three vertices and a color
     */
    Triangle(Point<CoordinateType> _a, Point<CoordinateType> _b, Point<CoordinateType> _c, sf::Color color);

    /*!
     * \brief Calculates barycentric coordinates of the given point.
     * \param p : a point (in most cases, a click performed by the user)
     * \return the barycentric coordinates of the point in the triangle
     *
     * A point is inside a triangle if all his coordinates are positive or negative
     */
    std::vector<CoordinateType> calculateBarycentricCoordinates(const Point<CoordinateType>& p) const;

    /*!
     * \brief Checks if the triangles is selected by the user
     * \param p : a point (in most cases, a click performed by the user)
     * \return true if the triangle is selected, returns else in the other case
     *
     * Returns true if the point p is inside the triangle.
     */
    bool isClicked(const Point<CoordinateType>& p) const;

    /*!
     * \brief Gets the center of a triangle
     * \return the center of the triangle
     *
     */
    Point<CoordinateType> center() const;

    /*!
     * \brief Rotates a triangle
     * \param center : the center
     * \param theta : the rotation (in radians)

     * Rotates the triangle around around center, with theta angle.
     */
    virtual void rotate(const Point<CoordinateType>& center, double theta);

    /*
    !!!!!!!!!!!
    TODO
    !!!!!!!!!!!
    */
    virtual void centralize(const Point<CoordinateType>& clickPos, const Point<CoordinateType>& relativePos);

    /*!
     * \brief Translates a triangle
     * \param translation : the translation performed
     *
     * Translates the triangle by the given translation.
     */
    virtual void translate(const Point<CoordinateType>& translation);

    /*!
     * \brief Gets the point from a triangle
     * \return a vector that contains the points
     *
     * Puts the points in a vector.
     */
	virtual std::vector<Point<CoordinateType>> getPoints() const;

	/*!
     * \brief Computes the distance between a triangle and a shape
     * \param shape : the other shape
     * \param points : the closest points from the current triangle and the shape
     * \return the distance between triangle and shape
     *
     * The distance between a triangle and a shape is the minimum distance between two vertices of shape and triangle.
     * These points are put in points vector to perform magnetism later.
     */
	virtual double distance(Shape<CoordinateType>* shape, std::vector<Point<CoordinateType>>& points) const;

	/*!
     * \brief Checks if the translated triangle is inside the window
     * \param translation : translation performed on the triangle
     *
     * If the translated triangle is outside the window (one vertex outside of the window), the translation is modified to avoid this.
     */
	virtual void isInsideWindow(Point<CoordinateType>& translation) const;

	/*!
     * \brief Reduces the size of current triangle
     * \param coeff : coefficient of decrease. Higher is the coefficient, smaller is the triangle
     *
     * Each vertex coordinates are divide by the coefficient to reduce the triangle's size.
     */
	virtual void reduceSize(int coeff);

	/*!
     * \brief Draw method
     * \param window : SFML window where the triangle is draw
     *
     * Draw the triangle in the window
     */
    void draw(sf::RenderWindow& window);

    /*!
     * \brief Print function
     * \param os : output stream
     * \param triangle : triangle to print
     *
     * Prints the triangle in the output stream os.
     */
    friend std::ostream& operator<< (std::ostream& os, const Triangle<CoordinateType>& triangle) {
        os << "Triangle : " << std::endl << "   Point A : " << triangle.a << std::endl << "   Point B : " << triangle.b << std::endl << "   Point C : " << triangle.c;
        return os;
    }
};

template<class CoordinateType>
Triangle<CoordinateType>::Triangle(Point<CoordinateType> _a, Point<CoordinateType> _b, Point<CoordinateType> _c, sf::Color color)
: a(_a), b(_b), c(_c), unrotatedA(_a), unrotatedB(_b), unrotatedC(_c), color(color){
    theta = 0;
}

/* Calculate the barycentric coordinates of the point
*/
template<class CoordinateType>
std::vector<CoordinateType> Triangle<CoordinateType>::calculateBarycentricCoordinates(const Point<CoordinateType>& p) const{
	std::vector<CoordinateType> barCoordinates;
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
    return Point<CoordinateType>((unrotatedA.getX() + unrotatedB.getX()+ unrotatedC.getX()) / 3, (unrotatedA.getY() + unrotatedB.getY() + unrotatedC.getY()) / 3);
}

/* Performs a rotation around another point with an angle theta
*/
template<class CoordinateType>
void Triangle<CoordinateType>::rotate(const Point<CoordinateType>& center, double theta) {
    this->theta += theta;
    a = unrotatedA.rotate(center, this->theta);
    b = unrotatedB.rotate(center, this->theta);
    c = unrotatedC.rotate(center, this->theta);
}

/* Centralize the triangle around the click position
*/
template<class CoordinateType>
void Triangle<CoordinateType>::centralize(const Point<CoordinateType>& clickPos, const Point<CoordinateType>& relativePos) {
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
    unrotatedA += translation;
    unrotatedB += translation;
    unrotatedC += translation;
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
std::vector<Point<CoordinateType>> Triangle<CoordinateType>::getPoints() const {
	std::vector<Point<CoordinateType>> points;
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
    std::vector<Point<CoordinateType>> selectedPiecePoints = this->getPoints();
    std::vector<Point<CoordinateType>> otherPoints = shape->getPoints();
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

template<class CoordinateType>
void Triangle<CoordinateType>::isInsideWindow(Point<CoordinateType>& translation) const {
    a.isInsideWindow(translation);
    b.isInsideWindow(translation);
    c.isInsideWindow(translation);
    //return (a.isInsideWindow(translation) && b.isInsideWindow(translation) && c.isInsideWindow(translation));
}

template<class CoordinateType>
void Triangle<CoordinateType>::reduceSize(int coeff) {
    unrotatedA.reduceSize(coeff);
    unrotatedB.reduceSize(coeff);
    unrotatedC.reduceSize(coeff);
    a.reduceSize(coeff);
    b.reduceSize(coeff);
    c.reduceSize(coeff);
}


