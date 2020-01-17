/**
 * Project Tangram
 */


#include "../Model/Triangle.h"
#include "Game.h"
#include "../Model/Piece.h"
#include "../Controller/FileUtils.h"
#include "Action.h"

Game * Game::init(const char * filename) {
	auto * smallTriangle1 = new Piece<int>(1, sf::Color(255, 100, 0),
											  0, 400, 100, 300, 200, 400);
	auto * smallTriangle2 = new Piece<int>(1, sf::Color(255, 255, 0),
											  200, 200, 300, 100, 300, 300);
	auto * mediumTriangle = new Piece<int>(1, sf::Color(0, 255, 0),
											  200, 400, 400, 200, 400, 400);
	auto * largeTriangle1 = new Piece<int>(1, sf::Color(150, 0, 100),
											  0, 0, 200, 200, 0, 400);
	auto * largeTriangle2 = new Piece<int>(1, sf::Color(255, 0, 150),
											  0, 0, 400, 0, 200, 200);
	auto * square = new Piece<int>(2, sf::Color(0, 0, 255),
											  100, 300, 200, 200, 200, 400,
											  200, 200, 300, 300, 200, 400);
	auto * parallelogram = new Piece<int>(2, sf::Color(0, 255, 255),
											  300, 100, 400, 0, 400, 200,
											  300, 100, 400, 200, 300, 300);

	Game * game = new Game;
    game->pieces.push_back(largeTriangle1);
	game->pieces.push_back(largeTriangle2);
	game->pieces.push_back(mediumTriangle);
	game->pieces.push_back(parallelogram);
	game->pieces.push_back(square);
	game->pieces.push_back(smallTriangle1);
	game->pieces.push_back(smallTriangle2);

	game -> goal = Piece<int>::createPiece(filename);
	std::vector<Point<int>> points = game->goal->getPoints();
	for(auto& point : points) {
        game->validGoalPoints[point] = false;
	}

	// boutons :
	// ???
	return game;
}

Game::Game() : selected(nullptr), relativePos(Point(0, 0)) {
}

void Game::draw(sf::RenderWindow& window) {
	window.clear();
	goal -> draw(window);
	for (auto s : pieces) {
		s -> draw(window);
	}
	window.display();
}

/* Select a piece when a left click is performed by the user
*/
void Game::select(const Point<int> & event) {
	selected = nullptr;
	for (auto s : pieces) {
		if (s->isClicked(event)){
			selected = s;
			relativePos = selected->center() - event;
		}
	}
}

void Game::deselect(const Point<int> & event) {
	if (selected != nullptr) {
		//selected->centralize(event, relativePos);
		magnetize();
		checkValidatedGoalPoints();
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
}

void Game::save() {
	std::vector<Point<int>> points;
	for_each(pieces.cbegin(), pieces.cend(), [&points](Shape<int> * s) {
		vector<Point<int>> shapePoints = s -> getPoints();
		points.insert(points.cend(), shapePoints.cbegin(), shapePoints.cend());
	});

	Point<int>::normalize(points);
	FileUtils::writeFile(points, "levels/save.txt");
}

void Game::magnetize() {
    double dist;
    double minDist = DBL_MAX;
    std::vector<Point<int>> points(2);
    std::vector<Point<int>> minPoints(2);
    Point<int> translation;
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

void Game::checkValidatedGoalPoints() {
    std::vector<Point<int>> goalPoints = goal->getPoints();
    std::vector<Point<int>> selectedPoints = selected->getPoints();
    for(auto& selectedPoint : selectedPoints) {
        for(auto& goalPoint : validGoalPoints) {
            if((selectedPoint.distance(goalPoint.first)) < 3) {
                validGoalPoints[goalPoint.first] = true;
            }
        }
    }

    //test
    /*for(auto& point : validGoalPoints) {
        cout << point.first << " " << point.second << std::endl;
    }*/
}
