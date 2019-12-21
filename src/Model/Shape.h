/**
 * Project Tangram
 */


#ifndef _SHAPE_H
#define _SHAPE_H

#include "../Controller/Clickable.h"
#include "../View/Drawable.h"
#include "Point.h"

template<class CoordinateType>
class Shape: public Clickable, public Drawable {
    virtual Point<CoordinateType> center() = 0;
    virtual void centralize(Point<CoordinateType> clickPos) = 0;
    virtual void rotate(Point<CoordinateType> center, double theta) = 0;
};

#endif //_SHAPE_H
