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
    Point<CoordinateType> a;
    Point<CoordinateType> b;
    Point<CoordinateType> c;

public :
    Triangle(Point<CoordinateType> _a, Point<CoordinateType> _b, Point<CoordinateType> _c);

    vector<CoordinateType> centroid(Point<CoordinateType> p);
    bool isInTriangle(Point<CoordinateType> p);

    // friends functions
    friend std::ostream& operator<< (std::ostream& os, const Triangle<CoordinateType>& triangle) {
        os << "Triangle : " << std::endl << "Point A : " << triangle.a << "Point B : " << triangle.b << "Point C : " << triangle.c << std::endl;
        return os;
    }
};

template<class CoordinateType>
Triangle<CoordinateType>::Triangle(Point<CoordinateType> _a, Point<CoordinateType> _b, Point<CoordinateType> _c)
: a(_a), b(_b), c(_c){
}

template<class CoordinateType>
vector<CoordinateType> Triangle<CoordinateType>::centroid(Point<CoordinateType> p) {
	vector<CoordinateType> centroid;
	vector<CoordinateType> pa = p.createVector(a);
	vector<CoordinateType> pb = p.createVector(b);
	vector<CoordinateType> pc = p.createVector(c);
	centroid.push_back((pb[0] * pc[1]) - (pb[1] * pc[0]));
	centroid.push_back((pc[0] * pa[1]) - (pc[1] * pa[0]));
	centroid.push_back((pa[0] * pb[1]) - (pa[1] * pb[0]));
	return centroid;
}

template<class CoordinateType>
bool Triangle<CoordinateType>::isInTriangle(Point<CoordinateType> p) {
	std::vector<CoordinateType> centroid = this->centroid(p);
	if(centroid[0] <= 0 && centroid[1] <= 0 && centroid[2] <= 0)
		return true;
	else if(centroid[0] >= 0 && centroid[1] >= 0 && centroid[2] >= 0)
		return true;
	return false;
}

#endif //_TRIANGLE_H
