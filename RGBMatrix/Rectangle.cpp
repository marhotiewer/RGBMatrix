#include "Rectangle.h"

Rectangle::Rectangle(Vector2i p1, Vector2i p2, RGB color, bool filled): Drawable(p1, color), p2(p2), filled(filled) {}

void Rectangle::draw(RGBMatrix &matrix) {
	if(filled) {
		for(int y = p1.y; y <= p2.y; y++) {
			for(int x = p1.x; x <= p2.x; x++) {
				matrix.setPixel(Vector2i(x, y), color);
			}
		}
	} else {
		for(int x = p1.x; x <= p2.x; x++) matrix.setPixel(Vector2i(x, p1.y), color);
		for(int x = p1.x; x <= p2.x; x++) matrix.setPixel(Vector2i(x, p2.y), color);
		for(int y = p1.y+1; y < p2.y; y++) matrix.setPixel(Vector2i(p1.x, y), color);
		for(int y = p1.y+1; y < p2.y; y++) matrix.setPixel(Vector2i(p2.x, y), color);
	}
}
