/**
 * Project Tangram
 */


#pragma once
#include "../Controller/Clickable.h"
#include "../View/Drawable.h"
#include "Point.h"

template<class CoordinateType>
class Shape: public Clickable, public Drawable {
public:
	virtual Point<CoordinateType> center() = 0;
	virtual void centralize(Point<CoordinateType> clickPos) = 0;
	virtual void rotate(Point<CoordinateType> center, double theta) = 0;
	virtual bool isInShape(Point<CoordinateType>& p) const = 0;

	void rotate(float theta) {
		rotate(center(), theta);
	}
};

