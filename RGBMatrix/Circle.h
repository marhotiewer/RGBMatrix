#ifndef CIRCLE_H
#define CIRCLE_H

#include "datatypes.hpp"
#include "Drawable.h"

///
/// @brief Drawable circle, this will draw a circle on the matrix.
///
class Circle: public Drawable {
	public:
		///
		/// @brief Constructor, initializes all properties with desired values.
		/// @param p1 The centre position of the circle.
		/// @param r The radius of the circle.
		/// @param color The colour of the circle.
		/// @param filled Set the circle to filled or hollow.
		///
		Circle(Vector2i p1, int r, RGB color, bool filled = false);
		void draw(RGBMatrix &matrix) override;
		void update() override;
		///
		/// @brief the speed and direction of the circle.
		///
		Vector2i delta;
		///
		/// @brief Decides if the circle is filled or not.
		///
		bool filled;
		///
		/// @brief The radius of the circle.
		///
		int r;
};

#endif
