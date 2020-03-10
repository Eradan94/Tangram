/**
 * Project Tangram
 */


#include "../../include/Model/Triangle.h"
#include "../../include/Controller/Game.h"
#include "../../include/Model/Piece.h"
#include "../../include/Controller/GameBuilder.h"

std::shared_ptr<Game> Game::init(const char * filename) {
	GameBuilder builder;

	builder.withShape(std::shared_ptr<Piece<double>>(new Piece<double>(2, sf::Color(255, 100, 0), littleTriangle1)));
	builder.withShape(std::shared_ptr<Piece<double>>(new Piece<double>(2, sf::Color(255, 255, 0), littleTriangle2)));
	builder.withShape(std::shared_ptr<Piece<double>>(new Piece<double>(4, sf::Color(0,   255, 0), mediumTriangle)));
	builder.withShape(std::shared_ptr<Piece<double>>(new Piece<double>(8, sf::Color(150, 0,   100), largeTriangle1)));
	builder.withShape(std::shared_ptr<Piece<double>>(new Piece<double>(8, sf::Color(255, 0,   150), largeTriangle2)));
	builder.withShape(std::shared_ptr<Piece<double>>(new Piece<double>(4, sf::Color(0,   0,   255), square)));
	builder.withShape(std::shared_ptr<Piece<double>>(new Piece<double>(4, sf::Color(0,   255, 255), parallelogram)));

	return builder.build(filename);
}

Game::Game():
	selected(nullptr), goal(nullptr), gameState(false) {
}

Game::Game(std::vector<std::shared_ptr<Shape<double>>> pieces, std::unique_ptr<Piece<double>> goal):
	selected(nullptr), relativePos(Point(0., 0.)), pieces(pieces), goal(std::move(goal)), gameState(false) {
}

void Game::draw(sf::RenderWindow& window) {
	if(goal != nullptr) {
        goal -> draw(window);
	}
	for (auto s : pieces) {
        s -> draw(window);
    }
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

void Game::deselect() {
	if (selected != nullptr) {
		magnetize();
		selected = nullptr;
	}
}

void Game::centralizeSelected(Point<double> point) {
	if (selected != nullptr) {
		selected -> centralize(point, relativePos);
	}
}

void Game::rotateSelected(const double d) {
	if (selected != nullptr) {
		selected->rotate(d);
	}
}

Game::~Game() {
}

void Game::save(std::string levelName) {
	std::vector<Point<double>> points;
	for_each(pieces.cbegin(), pieces.cend(), [&points](std::shared_ptr<Shape<double>> s) {
		std::vector<Point<double>> shapePoints = s -> getPoints();
		points.insert(points.cend(), shapePoints.cbegin(), shapePoints.cend());
	});
    std::string path = "levels/" + levelName + ".txt";
	Point<double>::normalize(points);
	FileUtils::writeFile(points, path);
}

void Game::magnetize() {
    double dist;
    double minDist = DBL_MAX;
    std::vector<Point<double>> points(2);
    std::vector<Point<double>> minPoints(2);
    Point<double> translation;
    Preferences * pref = Preferences::getInstance();
    // Get the shortest distance between two points from each shape
    for(auto& piece : pieces) {
        if(piece != selected) {
            dist = selected->distance(piece.get(), points);
            if(dist < minDist) {
                minDist = dist;
                minPoints = points;
            }
        }
    }
    // Magnetize with the goal
    if(goal != nullptr) {
        dist = selected->distance(goal.get(), points);
        if(dist < minDist) {
            minDist = dist;
            minPoints = points;
        }
    }
    if(minDist < pref -> getMagnetism()) { // if the distance is greater than the threshold, the piece is not magnetized
        translation = minPoints[1] - minPoints[0];
        selected->translate(translation);
    }
}

void Game::validateShape() {
    if(goal == nullptr) {
        return;
    }
    std::vector<Point<double>> goalPoints = goal->getPoints();
    std::vector<Point<double>> piecesPoints;
    std::vector<Point<double>> piecePoints;
    for(auto& piece : pieces) {
        piecePoints = piece->getPoints();
        piecesPoints.insert(piecesPoints.end(), piecePoints.begin(), piecePoints.end());
    }
    if(std::is_permutation(goalPoints.begin(), goalPoints.end(), piecesPoints.begin(), piecesPoints.end())) {
        gameState = true;
    }
}

bool Game::getGameState() {
    return gameState;
}

