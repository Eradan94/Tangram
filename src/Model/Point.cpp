/**
 * Project Tangram
 */


#include "Point.h"

template<>
inline bool Point<double>::operator==(const Point<double>& other) const {
	return this->distance(other) <= EPSILON;
}
