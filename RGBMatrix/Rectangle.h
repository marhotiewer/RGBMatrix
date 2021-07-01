#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "datatypes.hpp"
#include "Drawable.h"

///
/// @brief Drawable rectangle, this will draw a rectangle on the matrix.
///
class Rectangle: public Drawable {
	public:
		///
		/// @brief Constructor, initializes all properties with desired values.
		/// @param p1 Top left point of the rectangle.
		/// @param p2 Bottom right point of the rectangle.
		/// @param color The colour of the rectangle.
		/// @param filled Set the rectangle to filled or hollow.
		///
		Rectangle(Vector2i p1, Vector2i p2, RGB color, bool filled);
		void draw(RGBMatrix &matrix);
		///
		/// @brief Bottom right point of the rectangle.
		///
		Vector2i p2;
		///
		/// @brief Decides if the rectangle is filled or not.
		///
		bool filled;
};

#endif
