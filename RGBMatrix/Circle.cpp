#include "Circle.h"

Circle::Circle(Vector2i p1, int r, RGB color, bool filled): Drawable(p1, color), delta(Vector2i(1, 1)), filled(filled), r(r) {}

void Circle::draw(RGBMatrix &matrix) {
	int x=r, y=0;
	matrix.setPixel(Vector2i(x+p1.x, p1.y), color);
	if(r > 0) {
		if(!filled) {
			matrix.setPixel(Vector2i(p1.x, p1.y-x), color);
			matrix.setPixel(Vector2i(-y+p1.x, x+p1.y), color);
		} else {
			for(int i = p1.x-x+1; i<x+p1.x; i++) {
				matrix.setPixel(Vector2i(i, p1.y), color);
			}
		}
		matrix.setPixel(Vector2i(p1.x-x, p1.y), color);
	}
	int p=1-r;
	while(x>y) {
		y++;
		if(p<=0) {
			p=p+2*y+1;
		} else {
			x--;
			p=p+2*y-2*x+1;
		}
		if(x<y) break;
		if (!filled) {
			matrix.setPixel(Vector2i(x+p1.x, y+p1.y), color);
			matrix.setPixel(Vector2i(-x+p1.x, y+p1.y), color);
			matrix.setPixel(Vector2i(x+p1.x, -y+p1.y), color);
			matrix.setPixel(Vector2i(-x+p1.x, -y+p1.y), color);
		} else {
			for(int i = -x + p1.x; i <= x + p1.x; i++) {
				matrix.setPixel(Vector2i(i, y+p1.y), color);
				matrix.setPixel(Vector2i(i, -y+p1.y), color);
			}
		}
		if(x!=y) {
			if(!filled) {
				matrix.setPixel(Vector2i(y+p1.x, x+p1.y), color);
				matrix.setPixel(Vector2i(-y+p1.x, x+p1.y), color);
				matrix.setPixel(Vector2i(y+p1.x, -x+p1.y), color);
				matrix.setPixel(Vector2i(-y+p1.x, -x+p1.y), color);
			} else {
				for(int i=-y+p1.x; i<=y+p1.x; i++) {
					matrix.setPixel(Vector2i(i, x+p1.y), color);
					matrix.setPixel(Vector2i(i, -x+p1.y), color);
				}
			}
		}
	}
}

void Circle::update() {
	p1 += delta;

	if(p1.y+r >= 32 || p1.y-r <= 1) {
		delta.y *= -1;
	}
	if(p1.x+r >= 64 || p1.x-r <= 1) {
		delta.x *= -1;
	}
}
