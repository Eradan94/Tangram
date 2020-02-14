/**
 * Project Tangram
 */


#pragma once
#include "../../include/Controller/Clickable.h"
#include "../../include/View/Drawable.h"
#include "../../include/Model/Point.h"

template<class CoordinateType>
class Shape: public Clickable<CoordinateType>, public Drawable {
public:
	virtual Point<CoordinateType> center() const = 0;
	virtual void centralize(const Point<CoordinateType> clickPos, const Point<CoordinateType> relativePos) = 0;
	virtual void rotate(const Point<CoordinateType> center, double theta) = 0;
	virtual bool isClicked(const Point<CoordinateType>& p) const = 0;
	virtual std::vector<Point<CoordinateType>> getPoints() const = 0;
	virtual double distance(Shape<CoordinateType>* shape, std::vector<Point<double>>& points) const = 0;
	virtual void translate(const Point<CoordinateType>& translation) = 0;
	virtual void isInsideWindow(Point<CoordinateType>& translation) const = 0;
	virtual void reduceSize(int coeff) = 0;

	void rotate(const float theta) {
		rotate(center(), theta);
	}
};

