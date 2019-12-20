/**
 * Project Tangram
 */


#ifndef _TRIANGLE_H

#include <iostream>
#include <vector>

#include "Point.h"
#include "Shape.h"

template<class CoordinateType>
class Triangle: public Shape {
private :
    Point<CoordinateType>& a;
    Point<CoordinateType>& b;
    Point<CoordinateType>& c;

public :
    Triangle(Point<CoordinateType>& _a, Point<CoordinateType>& _b, Point<CoordinateType>& _c);

    vector<CoordinateType> calculateBarycentricCoordinates(Point<CoordinateType>& p) const;
    bool isInTriangle(Point<CoordinateType>& p) const;
    Point<CoordinateType> center();

    // friends functions
    friend std::ostream& operator<< (std::ostream& os, const Triangle<CoordinateType>& triangle) {
        os << "Triangle : " << std::endl << "   Point A : " << triangle.a << std::endl << "   Point B : " << triangle.b << std::endl << "   Point C : " << triangle.c;
        return os;
    }
};

template<class CoordinateType>
Triangle<CoordinateType>::Triangle(Point<CoordinateType>& _a, Point<CoordinateType>& _b, Point<CoordinateType>& _c)
: a(_a), b(_b), c(_c){
}

/* Calculate the barycentric coordinates of the point
*/
template<class CoordinateType>
vector<CoordinateType> Triangle<CoordinateType>::calculateBarycentricCoordinates(Point<CoordinateType>& p) const{
	vector<CoordinateType> barCoordinates;
	vector<CoordinateType> pa = p.createVector(a);
	vector<CoordinateType> pb = p.createVector(b);
	vector<CoordinateType> pc = p.createVector(c);
	barCoordinates.push_back((pb[0] * pc[1]) - (pb[1] * pc[0]));
	barCoordinates.push_back((pc[0] * pa[1]) - (pc[1] * pa[0]));
	barCoordinates.push_back((pa[0] * pb[1]) - (pa[1] * pb[0]));
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

#endif //_TRIANGLE_H
