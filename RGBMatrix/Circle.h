#ifndef CIRCLE_H
#define CIRCLE_H

#include "datatypes.hpp"
#include "Drawable.h"

class Circle: Drawable {
	public:
		Circle(Vector2i p1, int r, RGB color, bool filled = false);
		void draw(RGBMatrix &matrix) override;
		bool filled;
		int r;
};

#endif
