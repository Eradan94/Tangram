/*!
 * \file Piece.h
 * \brief Defines a representation of piece.
 * \author Biguenet Denis & Gosset Severin
 * \date 22/02/2020
 */

#pragma once

#include <list>
#include <cstdarg>

#include "../../include/Controller/FileUtils.h"
#include "../../include/Model/Shape.h"
#include "../../include/Model/Triangle.h"

/*! \class Piece
 * \brief Representation of piece
 *
 * A triangle is represented by a list of triangles.
 * This class is a template, mainly used with int, double, float or short types.
 */
template<class CoordinateType>
class Piece: public Shape<CoordinateType> {
public :
    /*!
     * \brief default constructor
     *
     */
    Piece();

	Piece(int size, sf::Color color, ...);

    /*!
     * \brief Create a piece from points and color
     * \param size : number of triangle in the piece
     * \param color : color of the piece
     * \param points : vertices of the piece
     *
     */
	Piece(int size, sf::Color color, const CoordinateType * points);

	/*!
     * \brief Create a piece from vector of points
     * \param color : color of the piece
     * \param points : vertices of the piece
     *
     */
	Piece(sf::Color color, std::vector<Point<CoordinateType>> points);

	/*!
     * \brief Create a piece from a file
     * \param filename : name of the file
     * \return a pointer to new piece
     */
	static std::unique_ptr<Piece<CoordinateType>> createPiece(const char * filename);

	/*!
     * \brief Adds a single triangle in the piece
     * \param t : the triangle added into the list of triangles
     */
    void addTriangle(Triangle<CoordinateType> t);

    /*!
     * \brief Translates a piece
     * \param translation : the performed translation
     *
     * The translation is performed on each piece's triangle to move the whole piece.
     */
    virtual void translate(const Point<CoordinateType>& translation);

    /*!
     * \brief Rotates a piece around a point
     * \param center : the center of the piece
     * \param theta : angle of rotation (in radians)
     *
     * The rotation is performed on each piece's triangle.
     */
    virtual void rotate(const Point<CoordinateType>& center, double theta);

    /*!
     * \brief Gets the piece's center
     * \return the center of the piece
     *
     * The center of the piece is the mean of the triangle's centers
     */
    virtual Point<CoordinateType> center() const;

    /*
    * !!!!!!!!!!!!!!!
    * TODO
    * !!!!!!!!!!!!!!!
    */
    virtual void centralize(const Point<CoordinateType>& clickPos, const Point<CoordinateType>& relativePos);

    /*!
     * \brief Check if the piece is selected by the user
     * \param p : a point (the position of the click)
     * \return true if the piece is selected, false in the other case
     *
     * Check if p is inside at least one triangle.
     */
	virtual bool isClicked(const Point<CoordinateType> & p) const;

	/*!
     * \brief Gets the points of the triangle
     * \return a vector of points
     *
     */
	virtual std::vector<Point<CoordinateType>> getPoints() const;

	/*!
     * \brief Computes the distance between a piece and a shape
     * \param shape : the other shape
     * \param points : the closest points from the current piece and the shape
     * \return the distance between piece and shape
     *
     * The distance between a piece and a shape is the minimum distance between two vertices of shape and triangle.
     * These points are put in points vector to perform magnetism later.
     */
	virtual double distance(Shape<CoordinateType>* shape, std::vector<Point<CoordinateType>>& points) const;

	/*!
     * \brief Checks if the translated piece is inside the window
     * \param translation : translation performed on the triangle
     *
     * If the translated piece is outside the window (one vertex outside the window), the translation is modified to avoid this.
     */
	virtual void isInsideWindow(Point<CoordinateType>& translation) const;

    /*!
     * \brief Reduces the size of current piece
     * \param coeff : coefficient of decrease. Higher is the coefficient, smaller is the piece
     *
     * Each vertex coordinates are divide by the coefficient to reduce the piece's size.
     */
	virtual void reduceSize(int coeff);

	/*!
     * \brief Draw method
     * \param window : SFML window where the piece is draw
     *
     * Draws the piece in the window (draws each piece's triangle)
     */
    void draw(sf::RenderWindow& window);

    /*!
     * \brief Print function
     * \param os : output stream
     * \param piece : piece to print
     *
     * Prints the piece in the output stream os.
     */
    friend std::ostream& operator<< (std::ostream& os, const Piece<CoordinateType>& piece) {
        os << "Piece : " << std::endl;
        for(auto& t : piece.triangles) {
            os << t << std::endl;
        }
        return os;
    }

private :
    std::list<Triangle<CoordinateType>> triangles; /*!List of triangles*/
};

template<class CoordinateType>
Piece<CoordinateType>::Piece()= default;

// Creates a Piece using a color and a list of coordinates.
// Coordinates are grouped by 3, each group is a triangle.
// Piece(3, color,
// 		x11, y11, x12, y12, x13, y13,
// 		x21, y21, x22, y22, x23, y23,
//		x31, y31, x32, y32, x33, y33);
template<class CoordinateType>
Piece<CoordinateType>::Piece(int size, sf::Color color, ...) {
	va_list args;
	va_start(args, color);

	for(int i = 0; i < size; i++) {
		CoordinateType x = va_arg(args, CoordinateType);
		CoordinateType y = va_arg(args, CoordinateType);
		Point<CoordinateType> p1 = Point<CoordinateType>(x, y);
		x = va_arg(args, CoordinateType);
		y = va_arg(args, CoordinateType);
		Point<CoordinateType> p2 = Point<CoordinateType>(x, y);
		x = va_arg(args, CoordinateType);
		y = va_arg(args, CoordinateType);
		Point<CoordinateType> p3 = Point<CoordinateType>(x, y);
		Triangle<CoordinateType> t(p1, p2, p3, color);
		triangles.push_back(t);
	}

	va_end(args);
}

template<class CoordinateType>
Piece<CoordinateType>::Piece(int size, sf::Color color, const CoordinateType * points) {
	for(int i = 0; i < size; i++) {
		CoordinateType x = points[i * 6];
		CoordinateType y = points[i * 6 + 1];
		Point<CoordinateType> p1 = Point<CoordinateType>(x, y);
		x = points[i * 6 + 2];
		y = points[i * 6 + 3];
		Point<CoordinateType> p2 = Point<CoordinateType>(x, y);
		x = points[i * 6 + 4];
		y = points[i * 6 + 5];
		Point<CoordinateType> p3 = Point<CoordinateType>(x, y);
		Triangle<CoordinateType> t(p1, p2, p3, color);
		triangles.push_back(t);
	}
}

template<class CoordinateType>
Piece<CoordinateType>::Piece(sf::Color color, std::vector<Point<CoordinateType>> points) {
	Point<double> offsetPoint(600, 50);
	for(int i = 0; i < (int)points.size() / 3; i++) {
		Point<CoordinateType> p1 = points[i * 3 ] + offsetPoint;
		Point<CoordinateType> p2 = points[i * 3 + 1] + offsetPoint;
		Point<CoordinateType> p3 = points[i * 3 + 2] + offsetPoint;
		Triangle<CoordinateType> t(p1, p2, p3, color);
		triangles.push_back(t);
	}
}

/* Add a single triangle in the list
*/
template<class CoordinateType>
void Piece<CoordinateType>::addTriangle(const Triangle<CoordinateType> t) {
    triangles.push_back(t);
}

/* calculate the piece's center
*/
template<class CoordinateType>
Point<CoordinateType> Piece<CoordinateType>::center() const {
    Point<CoordinateType> center;
    for(auto& t : triangles) {
        center += t.center();
    }
    return center / triangles.size();
}

/* Performs a rotation with an angle theta
*/
template<class CoordinateType>
void Piece<CoordinateType>::rotate(const Point<CoordinateType>& center, double theta) {
    //Point<CoordinateType> c = center();
    for(auto& t : triangles) {
        t.rotate(center, theta);
    }
}

/* Centralize the piece on the mouse cursor
*/
template<class CoordinateType>
void Piece<CoordinateType>::centralize(const Point<CoordinateType>& clickPos, const Point<CoordinateType>& relativePos) {
    Point<CoordinateType> point = center() - relativePos;
    Point<CoordinateType> translation = clickPos - point;
    isInsideWindow(translation);
    translate(translation);
}

/* Translate a piece
*/
template<class CoordinateType>
void Piece<CoordinateType>::translate(const Point<CoordinateType>& translation) {
    for(auto& t : triangles) {
        t.translate(translation);
    }
}

/* draw a piece
*/
template<class CoordinateType>
void Piece<CoordinateType>::draw(sf::RenderWindow& window) {
    for(auto& t : triangles) {
        t.draw(window);
    }
}

/* return true if the point p is inside the piece
*/
template<class CoordinateType>
bool Piece<CoordinateType>::isClicked(const Point<CoordinateType> &p) const{
    // Verify for each triangle if the point is inside it
	for(auto& t : triangles) {
		if(t.isClicked(p)) {
			return true;
		}
	}
	return false;
}

template<class CoordinateType>
std::vector<Point<CoordinateType>> Piece<CoordinateType>::getPoints() const {
	std::vector<Point<CoordinateType>> points;
	for_each(triangles.cbegin(), triangles.cend(), [&points](Triangle<CoordinateType> t){
		std::vector<Point<CoordinateType>> trianglePoints = t.getPoints();
		points.insert(points.cend(), trianglePoints.cbegin(), trianglePoints.cend());
	});

	return points;
}

/* Calculate the distance between a piece and another shape.
* The distance between two triangles is the shortest distance between two points from each shape
* points represents the couple of points, to get the translation to perform
*/
template<class CoordinateType>
double Piece<CoordinateType>::distance(Shape<CoordinateType>* shape, std::vector<Point<CoordinateType>>& points) const {
    std::vector<Point<CoordinateType>> minPoints;
    double minDist = DBL_MAX;
    double dist;
    for(auto& triangle : this->triangles) {
        dist = triangle.distance(shape, points);
        if(dist < minDist) {
            minDist = dist;
            minPoints = points;
        }
    }
    points = minPoints;
    return minDist;
}

template<class CoordinateType>
std::unique_ptr<Piece<CoordinateType>> Piece<CoordinateType>::createPiece(const char *filename) {
	std::vector<Point<CoordinateType>> points = FileUtils::readFile(filename);
	return std::move(std::unique_ptr<Piece<CoordinateType>>(new Piece(sf::Color(255, 255, 255), points)));
}

template<class CoordinateType>
void Piece<CoordinateType>::isInsideWindow(Point<CoordinateType>& translation) const {
    for(auto& triangle : this->triangles) {
        triangle.isInsideWindow(translation);
    }
}

template<class CoordinateType>
void Piece<CoordinateType>::reduceSize(int coeff) {
    for(auto& triangle : this->triangles) {
        triangle.reduceSize(coeff);
    }
}
