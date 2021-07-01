#ifndef DATATYPES_HPP
#define DATATYPES_HPP

///
/// @brief Simple struct to represent a point on the screen.
///
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
	Vector2i& operator+=(const Vector2i& rhs) {
		this->x += rhs.x;
		this->y += rhs.y;
		return *this;
	}
};

///
/// @brief Simple struct to represent a colour.
/// @details We are friending RGBMatrix because the draw function needs to be able to access the color_code.
/// In the constructor we shift R, G and B bits into color_code, high level code has no business with this variable,
/// so we are keeping it private except for RGBMatrix which needs the values to draw the pixels.
///
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
