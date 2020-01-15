//
// Created by odomar on 14/01/2020.
//

#include "Polygon.h"

Polygon::Polygon() {
	update();
}

size_t Polygon::getPointCount() const {
	return points.size();
}

sf::Vector2f Polygon::getPoint(std::size_t index) const {
	Point<double> p = points[index];
	return sf::Vector2f(p.getX(), p.getY());
}

void Polygon::setPoint(int index, Point<double> p) {
	points[index] = p;
	update();
}

void Polygon::setPointCount(int count) {
	points.resize(count);
	update();
}
