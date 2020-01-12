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
	virtual Point<CoordinateType> center() const = 0;
	virtual void centralize(const Point<CoordinateType> clickPos) = 0;
	virtual void rotate(const Point<CoordinateType> center, double theta) = 0;
	virtual bool isInShape(const Point<CoordinateType>& p) const = 0;

	void rotate(const float theta) {
		rotate(center(), theta);
	}
};

