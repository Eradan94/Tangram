/**
 * Project Tangram
 */


#pragma once

#include <list>
#include <cstdarg>

#include "Shape.h"
#include "Triangle.h"

template<class CoordinateType>
class Piece: public Shape<CoordinateType> {
public :
    Piece();
	Piece(int size, sf::Color color, ...);
    void addTriangle(const Triangle<CoordinateType> t);
    //void addTriangles(std::initializer_list<Triangle<CoordinateType>> triangles);
    virtual void rotate(Point<CoordinateType> center, double theta);
    virtual Point<CoordinateType> center();
    virtual void centralize(Point<CoordinateType> clickPos);

    void draw(sf::RenderWindow& window);

    // friends functions
    friend std::ostream& operator<< (std::ostream& os, const Piece<CoordinateType>& piece) {
        os << "Piece : " << std::endl;
        for(auto& t : piece.triangles) {
            os << t << std::endl;
        }
        return os;
    }

private :
    std::list<Triangle<CoordinateType>> triangles;
};

template<class CoordinateType>
Piece<CoordinateType>::Piece(){
}

// Creates a Piece using a color and a list of coordinates.
// Coordinates are grouped by 3, each group is a triangle.
// Piece(3, color,
// 		x11, y11, x12, y12, x13, y13,
// 		x21, y21, x22, y22, x23, y23,
//		x31, y31, x32, y32, x33, y33);
template<class CoordinateType>
Piece<CoordinateType>::Piece(int size, sf::Color color, ...) {
	va_list args;
	va_start(args, color);

	for(int i = 0; i < size; i++) {
		CoordinateType x = va_arg(args, CoordinateType);
		CoordinateType y = va_arg(args, CoordinateType);
		Point<CoordinateType> p1 = Point<CoordinateType>(x, y);
		x = va_arg(args, CoordinateType);
		y = va_arg(args, CoordinateType);
		Point<CoordinateType> p2 = Point<CoordinateType>(x, y);
		x = va_arg(args, CoordinateType);
		y = va_arg(args, CoordinateType);
		Point<CoordinateType> p3 = Point<CoordinateType>(x, y);
		Triangle<CoordinateType> t(p1, p2, p3, color);
		triangles.push_back(t);
	}
}

/* Add a single triangle in the list
*/
template<class CoordinateType>
void Piece<CoordinateType>::addTriangle(const Triangle<CoordinateType> t) {
    triangles.push_back(t);
}

/* add several triangles in the list
*/
/*template<class CoordinateType>
void Piece<CoordinateType>::addTriangles(std::initializer_list<Triangle<CoordinateType>> triangles) {
    this->triangles.insert(this->triangles.end(), triangles.begin(), triangles.end());
}*/

/* calculate the piece's center
*/
template<class CoordinateType>
Point<CoordinateType> Piece<CoordinateType>::center() {
    Point<CoordinateType> center;
    for(auto& t : triangles) {
        center += t.center();
    }
    return center / triangles.size();
}

/* Performs a rotation with an angle theta
*/
template<class CoordinateType>
void Piece<CoordinateType>::rotate(Point<CoordinateType> center, double theta) {
    //Point<CoordinateType> c = center();
    for(auto& t : triangles) {
        t.rotate(center, theta);
    }
}

/* Centralize the piece on the mouse cursor
*/
template<class CoordinateType>
void Piece<CoordinateType>::centralize(Point<CoordinateType> clickPos) {
    Point<CoordinateType> c = center();
    Point<CoordinateType> translation = clickPos - c;
    for(auto& t : triangles) {
        t.translate(translation);
    }
}

/* draw a piece
*/
template<class CoordinateType>
void Piece<CoordinateType>::draw(sf::RenderWindow& window) {
    for(auto& t : triangles) {
        t.draw(window);
    }
}
