#pragma once

#include <SFML/Graphics.hpp>
#include "Point.h"

class Polygon : public sf::Shape {
public:
	Polygon();
	virtual unsigned long getPointCount() const;
	virtual sf::Vector2f getPoint(std::size_t index) const;
	void setPoint(int index, Point<double> p);

	void setPointCount(int count);

private:
	std::vector<Point<double>> points;
};
