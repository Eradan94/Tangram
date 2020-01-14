#pragma once

#include <vector>
#include "../View/Drawable.h"
#include "Point.h"
#include "Polygon.h"

class Figure : public Drawable {
public:
	static Figure * createFigure(const char * filename);

	void draw(sf::RenderWindow &window);
private:
	std::vector<Point<double>> points;
	Polygon poly;
};
