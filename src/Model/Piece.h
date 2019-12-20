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
    //void addTriangles(std::initializer_list<Triangle<CoordinateType>> triangles);
    Point<CoordinateType> center();

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
    std::cout << "size : " << triangles.size() << std::endl;
    for(auto& t : triangles) {
        center += t.center();
    }
    return center / triangles.size();
}

#endif //_PIECE_H
