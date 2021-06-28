#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "datatypes.hpp"
#include "Drawable.h"

class Rectangle: public Drawable {
	public:
		Rectangle(Vector2i p1, Vector2i p2, RGB color, bool filled);
		void draw(RGBMatrix &matrix);
		Vector2i p2;
		bool filled;
};

#endif
