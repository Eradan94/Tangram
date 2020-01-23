/**
 * Project Tangram
 */


#include "Point.h"

template<>
bool Point<double>::operator==(const Point<double>& other) const {
	// epsilon
	return (x == other.x && y == other.y);
}
