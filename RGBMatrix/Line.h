#ifndef LINE_H
#define LINE_H

#include "datatypes.hpp"
#include "Drawable.h"

///
/// @brief Drawable line, this will draw a line on the matrix.
///
class Line: public Drawable {
	public:
		///
		/// @brief Constructor, initializes all properties with desired values.
		/// @param p1 The first point of the line.
		/// @param p2 The secion point of the line.
		/// @param color The colour of the line, defaults to white.
		///
		Line(Vector2i p1, Vector2i p2, RGB color = RGB(1, 1, 1));
		void draw(RGBMatrix &matrix) override;
		///
		/// @brief The second point of the line.
		///
		Vector2i p2;
};

#endif
