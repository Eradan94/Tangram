/**
 * Project Tangram
 */

#pragma once

#include "../Model/Point.h"

template<class CoordinateType>
class Clickable {
	virtual bool isClicked(const Point<CoordinateType>& p) const = 0;
};

