#ifndef DATATYPES_HPP
#define DATATYPES_HPP

struct Vector2i {
    int x, y;
	Vector2i(int x, int y): x(x), y(y) {}
	Vector2i operator+(const Vector2i& rhs) {
		return Vector2i(this->x + rhs.x, this->y + rhs.y);
	}
	bool operator>=(const Vector2i& rhs) {
		return (this->x >= rhs.x && this->y >= rhs.y);
	}
	bool operator<=(const Vector2i& rhs) {
		return (this->x <= rhs.x && this->y <= rhs.y);
	}
};

struct RGB {
	friend class RGBMatrix;
	private:
		char color_code { 0x00 };
	public:
		RGB(bool r, bool g, bool b) {
			color_code |= r << 0;
			color_code |= g << 1;
			color_code |= b << 2;
	}
};

#endif
