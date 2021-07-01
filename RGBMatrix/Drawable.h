#ifndef DRAWABLE_H
#define DRAWABLE_H

#include "datatypes.hpp"
#include "RGBMatrix.h"

///
/// @brief Abstract class for objects to be drawn on the led matrix and updated
///
class Drawable {
	public:
		///
		/// @brief Constructor, takes a position a colour. Sometimes a drawable has a second or even more positions so this cant be used as a point of origin.
		/// @param p1 Every drawable requires at least one position.
		/// @param color Every drawable requires to have a colour.
		///
		Drawable(Vector2i p1, RGB color): p1(p1), color(color) {}
		///
		///	@brief Draws the object on the matrix
		/// @details Pure virtual draw function, speaks for itself. This function will provide you with setPixel from RGBMatrix, use this to draw any shape or object
		/// with an algorythm using the position and colour.
		/// @param matrix Reference to RGBMatrix to provide access to setPixel allowing you to draw on the screen.
		///
		virtual void draw(RGBMatrix &matrix) = 0;
		///
		/// @brief updates the object every frame, position size etc.
		///
		virtual void update() = 0;
		///
		/// @brief Position of the drawable, implementation can differ.
		///
		Vector2i p1;
		///
		/// @brief The colour of the object, implementation can differ.
		///
		RGB color;
};

#endif
