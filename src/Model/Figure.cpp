//
// Created by odomar on 14/01/2020.
//

#include <FileUtils.h>
#include "Figure.h"

Figure * Figure::createFigure(const char *filename) {
	//Goal Test
	auto * fig = new Figure();
	fig->points = FileUtils::readFile(filename);

	// definit les points
	fig->poly.setPointCount(fig->points.size());
	for (int i = 0; i < fig->points.size(); i ++) {
		fig->poly.setPoint(i, fig->points[i]);
	}

	fig->poly.setFillColor(sf::Color(0, 0, 0));
	fig->poly.setOutlineColor(sf::Color(255, 255, 255));
	fig->poly.setOutlineThickness(2);

	return fig;
}

void Figure::draw(sf::RenderWindow& window) {
	window.draw(poly);
}
