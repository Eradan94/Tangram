/**
 * Project Tangram
 */


#pragma once

#include "../../include/View/Drawable.h"
#include "../../include/View/Button.h"
#include "../../include/Model/Shape.h"
#include "../../include/Model/Piece.h"
#include "../../include/View/Menu.h"

#include <list>
#include <vector>
#include <cfloat>
#include <memory>

class Game {
public :
	static std::shared_ptr<Game> init(const char * filename);

	static std::shared_ptr<Game> init();

	Game(std::vector<std::shared_ptr<Shape<double>>> pieces, std::unique_ptr<Piece<double>> goal);

	Game();

	~Game();

	void draw(sf::RenderWindow & window);

	void select(const Point<double> & event);

	void deselect(const Point<double> & event);

	void centralizeSelected(const sf::Event::MouseMoveEvent event);

	void rotateSelected(const double d);

	void save();

	void magnetize();

	void validateShape();

	bool getGameState();

private :
	std::vector<std::shared_ptr<Shape<double>>> pieces;
	std::shared_ptr<Shape<double>> selected;
	std::unique_ptr<Piece<double>> goal;
	Point<double> relativePos;
	bool gameState;

	// All shapes
	// little triangles
	static constexpr double littleTriangle1[2 * 3 * 2] = {
			100., 300., 100., 400., 000., 400.,
			100., 300., 200., 400., 100., 400.
	};
	static constexpr double littleTriangle2[2 * 3 * 2] = {
			200., 200., 300., 100., 300., 200.,
			200., 200., 300., 200., 300., 300.
	};

	// medium triangle
	static constexpr double mediumTriangle[2 * 3 * 4] = {
			300., 300., 300., 400., 200., 400.,
			300., 300., 400., 400., 300., 400.,
			300., 300., 400., 300., 400., 400.,
			300., 300., 400., 200., 400., 300.
	};

	// large triangle
	static constexpr double largeTriangle1[2 * 3 * 8] = {
			100., 100., 000., 000., 100., 000.,
			100., 100., 100., 000., 200., 000.,
			100., 100., 200., 000., 200., 100.,
			100., 100., 200., 100., 200., 200.,
			300., 100., 200., 200., 200., 100.,
			300., 100., 200., 100., 200., 000.,
			300., 100., 200., 000., 300., 000.,
			300., 100., 300., 000., 400., 000.
	};
	static constexpr double largeTriangle2[2 * 3 * 8] = {
			100., 100., 000., 000., 000., 100.,
			100., 100., 000., 100., 000., 200.,
			100., 100., 000., 200., 100., 200.,
			100., 100., 100., 200., 200., 200.,
			100., 300., 200., 200., 100., 200.,
			100., 300., 100., 200., 000., 200.,
			100., 300., 000., 200., 000., 300.,
			100., 300., 000., 300., 000., 400.
	};

	// square
	static constexpr double square[2 * 3 * 4] = {
			200., 300., 100., 300., 200., 200.,
			200., 300., 200., 200., 300., 300.,
			200., 300., 300., 300., 200., 400.,
			200., 300., 200., 400., 100., 300.
	};

	// parallelogram
	static constexpr double parallelogram[2 * 3 * 4] = {
			300., 100., 400., 000., 400., 100.,
			300., 100., 400., 100., 400., 200.,
			400., 200., 300., 100., 300., 200.,
			400., 200., 300., 200., 300., 300.
	};
};
