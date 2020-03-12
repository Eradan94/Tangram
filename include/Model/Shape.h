/*! \class Shape
 * \brief Interface for shapes (triangles and pieces)
 *
 */

#include <memory>

#pragma once
#include "../../include/Controller/Clickable.h"
#include "../../include/View/Drawable.h"
#include "../../include/Model/Point.h"

/*! \interface Shape
 * \brief Interface for shapes (triangles and pieces)
 *
 */
template<class CoordinateType>
class Shape: public Clickable<CoordinateType>, public Drawable {
public:
    /*!
     * \brief Gets the shape's center
     * \return the center of the shape
     *
     */
	virtual Point<CoordinateType> center() const = 0;

	/*!
	 * \brief Centralize the shape, relatively to the given position.
	 * This makes the shape follow mouse position while keeping the relative position to the initial click
	 * \param clickPos the click position to follow
	 * \param relativePos the relative position of the initial click
	 */
	virtual void centralizeRelative(const Point<CoordinateType>& clickPos, const Point<CoordinateType>& relativePos) = 0;

    /*!
     * \brief Rotates a shape around a point
     * \param center : the center of the shape or another point
     * \param theta : angle of rotation (in radians)
     *
     */
	virtual void rotate(const Point<CoordinateType>& center, double theta) = 0;

    /*!
     * \brief Check if the shape is selected by the user
     * \param p : a point (the position of the click)
     * \return true if the shape is selected, false in the other case
     *
     */
	virtual bool isClicked(const Point<CoordinateType>& p) const = 0;

    /*!
     * \brief Gets the points of the shape
     * \return a vector of points
     *
     */
	virtual std::vector<Point<CoordinateType>> getPoints() const = 0;

    /*!
     * \brief Computes the distance between a shape and another shape
     * \param shape : the other shape
     * \param points : the closest points from the current shape and the other shape
     * \return the distance between shape and the other shape
     *
     * The distance between two shapes is the minimum distance between two vertices of shape and other shape.
     * These points are put in points vector to perform magnetism later.
     */
	virtual double distance(Shape<CoordinateType>* shape, std::vector<Point<double>>& points) const = 0;

    /*!
     * \brief Translates a shape
     * \param translation : the performed translation
     *
     */
	virtual void translate(const Point<CoordinateType>& translation) = 0;

	/*!
     * \brief Checks if the translated shape is inside the window
     * \param translation : translation performed
     *
     * If the translated shape is outside the window (one vertex outside the window), the translation is modified to avoid this.
     */
	virtual void isInsideWindow(Point<CoordinateType>& translation) const = 0;

    /*!
     * \brief Reduces the size of current shape
     * \param coeff : coefficient of decrease. Higher is the coefficient, smaller is the shape
     *
     */
	virtual void reduceSize(int coeff) = 0;

	/*!
     * \brief Rotates a shape around the center of the shape
     * \param theta : angle of rotation (in radians)
     *
     */
	void rotate(const float theta) {
		rotate(center(), theta);
	}
};

