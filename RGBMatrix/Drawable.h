#ifndef DRAWABLE_H
#define DRAWABLE_H

#include "datatypes.hpp"
#include "RGBMatrix.h"

class Drawable {
	public:
		Drawable(Vector2i p1, RGB color): p1(p1), color(color) {}
		virtual void draw(RGBMatrix &matrix) = 0;
		Vector2i p1;
		RGB color;
};

#endif
