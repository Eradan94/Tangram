/**
 * Project Tangram
 */


#include "../Model/Triangle.h"
#include "Game.h"
#include "../Model/Piece.h"
#include "GameBuilder.h"

Game * Game::init(const char * filename) {
	GameBuilder builder;

	builder.withShape(new Piece<double>(2, sf::Color(255, 100, 0),
			100., 300., 100., 400., 000., 400.,
			100., 300., 200., 400., 100., 400.));
	builder.withShape(new Piece<double>(2, sf::Color(255, 255, 0),
			200., 200., 300., 100., 300., 200.,
			200., 200., 300., 200., 300., 300.));
	builder.withShape(new Piece<double>(4, sf::Color(0, 255, 0),
			300., 300., 300., 400., 200., 400.,
			300., 300., 400., 400., 300., 400.,
			300., 300., 400., 300., 400., 400.,
			300., 300., 400., 200., 400., 300.));
	builder.withShape(new Piece<double>(8, sf::Color(150, 0, 100.),
			100., 100., 000., 000., 100., 000.,
			100., 100., 100., 000., 200., 000.,
			100., 100., 200., 000., 200., 100.,
			100., 100., 200., 100., 200., 200.,
			300., 100., 200., 200., 200., 100.,
			300., 100., 200., 100., 200., 000.,
			300., 100., 200., 000., 300., 000.,
			300., 100., 300., 000., 400., 000.));
	builder.withShape(new Piece<double>(8, sf::Color(255, 0, 150),
			100., 100., 000., 000., 000., 100.,
			100., 100., 000., 100., 000., 200.,
			100., 100., 000., 200., 100., 200.,
			100., 100., 100., 200., 200., 200.,
			100., 300., 200., 200., 100., 200.,
			100., 300., 100., 200., 000., 200.,
			100., 300., 000., 200., 000., 300.,
			100., 300., 000., 300., 000., 400.));
	builder.withShape(new Piece<double>(4, sf::Color(0, 0, 255),
			200., 300., 100., 300., 200., 200.,
			200., 300., 200., 200., 300., 300.,
			200., 300., 300., 300., 200., 400.,
			200., 300., 200., 400., 100., 300.));
	builder.withShape(new Piece<double>(4, sf::Color(0, 255, 255),
			300., 100., 400., 000., 400., 100.,
			300., 100., 400., 100., 400., 200.,
			400., 200., 300., 100., 300., 200.,
			400., 200., 300., 200., 300., 300.));

	/*builder.withButton(new Button(1200, 50, 1425, 175, "<<"));
	builder.withButton(new Button(1450, 50, 1700, 175, ">>"));
	builder.withButton(new Button(1200, 200, 1425, 325, "Load"));
	builder.withButton(new Button(1450, 200, 1700, 325, "Save"));
	builder.withButton(new Button(1200, 350, 1700, 475, "Quit"));*/

	return builder.build(filename);
}

Game::Game(Menu * menu, std::vector<Shape<double> *> pieces, Piece<double> * goal):
	selected(nullptr), relativePos(Point(0., 0.)), menu(menu), pieces(pieces), goal(goal) {
}

void Game::draw(sf::RenderWindow& window) {
	window.clear();
	goal -> draw(window);
	menu -> draw(window);
	for (auto s : pieces) {
		s -> draw(window);
	}
	window.display();
}

/* Select a piece when a left click is performed by the user
*/
void Game::select(const Point<double> & event) {
	selected = nullptr;
	for (auto s : pieces) {
		if (s->isClicked(event)){
			selected = s;
			relativePos = selected->center() - event;
		}
	}
}

void Game::deselect(const Point<double> & event) {
	if (selected != nullptr) {
		//selected->centralize(event, relativePos);
		magnetize();
		checkPoints();
		selected = nullptr;
	}
}

void Game::centralizeSelected(sf::Event::MouseMoveEvent event) {
	if (selected != nullptr) {
		selected -> centralize(event, relativePos);
	}
}

void Game::rotateSelected(const double d) {
	if (selected != nullptr) {
		selected->rotate(d);
	}
}

Game::~Game() {
	delete goal;
	delete menu;
	for (auto * piece : pieces){
		delete piece;
	}
}

void Game::save() {
	std::vector<Point<double>> points;
	for_each(pieces.cbegin(), pieces.cend(), [&points](Shape<double> * s) {
		vector<Point<double>> shapePoints = s -> getPoints();
		points.insert(points.cend(), shapePoints.cbegin(), shapePoints.cend());
	});
	Point<double>::normalize(points);
	FileUtils::writeFile(points, "levels/save.txt");
}

void Game::magnetize() {
    double dist;
    double minDist = DBL_MAX;
    std::vector<Point<double>> points(2);
    std::vector<Point<double>> minPoints(2);
    Point<double> translation;
    // Get the shortest distance between two points from each shape
    for(auto& piece : pieces) {
        if(piece != selected) {
            dist = selected->distance(piece, points);
            if(dist < minDist) {
                minDist = dist;
                minPoints = points;
            }
        }
    }
    // Magnetize with the goal
    dist = selected->distance(goal, points);
    if(dist < minDist) {
        minDist = dist;
        minPoints = points;
    }
    if(minDist < 20) { // if the distance is greater than the threshold, the piece is not magnetized
        translation = minPoints[1] - minPoints[0];
        selected->translate(translation);
    }
}

void Game::checkPoints() {
    std::vector<Point<double>> goalPoints = goal->getPoints();
    std::vector<Point<double>> piecesPoints;
    std::vector<Point<double>> piecePoints;
    for(auto& piece : pieces) {
        piecePoints = piece->getPoints();
        piecesPoints.insert(piecesPoints.end(), piecePoints.begin(), piecePoints.end());
    }
    cout << std::is_permutation(goalPoints.begin(), goalPoints.end(), piecesPoints.begin(), piecesPoints.end()) << std::endl;
}

