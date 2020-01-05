/**
 * Project Tangram
 */


#pragma once

#include <list>

#include "Shape.h"
#include "Triangle.h"

template<class CoordinateType>
class Piece: public Shape<CoordinateType> {
public :
    Piece();

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
