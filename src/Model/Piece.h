/**
 * Project Tangram
 */


#ifndef _PIECE_H

#include <list>
#include<stdarg.h>

#include "Shape.h"
#include "Triangle.h"

template<class CoordinateType>
class Piece: public Shape {
public :
    Piece();

    void addTriangle(const Triangle<CoordinateType> t);
    void addTriangles(std::list<Triangle<CoordinateType>> triangles);

private :
    std::list<Triangle<CoordinateType>> triangles;
};

template<class CoordinateType>
Piece<CoordinateType>::Piece(){

}


template<class CoordinateType>
void Piece<CoordinateType>::addTriangle(const Triangle<CoordinateType> t) {
    triangles.push_back(t);
}

template<class CoordinateType>
void Piece<CoordinateType>::addTriangles(std::list<Triangle<CoordinateType>> triangles) {
    this->triangles = triangles;
}

#endif //_PIECE_H
