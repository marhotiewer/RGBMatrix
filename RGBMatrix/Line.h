#ifndef LINE_H
#define LINE_H

#include "datatypes.hpp"
#include "Drawable.h"

class Line: public Drawable {
	public:
		Line(Vector2i p1, Vector2i p2, RGB color = RGB(1, 1, 1));
		void draw(RGBMatrix &matrix) override;
		Vector2i p2;
};

#endif
