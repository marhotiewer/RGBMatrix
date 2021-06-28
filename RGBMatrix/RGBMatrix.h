#ifndef RGBMATRIX_H
#define RGBMATRIX_H

#include "hwlib.hpp"
#include "datatypes.hpp"

class RGBMatrix {
	public:
		RGBMatrix(hwlib::target::pin_out &A, hwlib::target::pin_out &B, hwlib::target::pin_out &C, hwlib::target::pin_out &D,
				  hwlib::target::pin_out &UR, hwlib::target::pin_out &UG, hwlib::target::pin_out &UB,
				  hwlib::target::pin_out &LR, hwlib::target::pin_out &LG, hwlib::target::pin_out &LB,
				  hwlib::target::pin_out &LAT, hwlib::target::pin_out &CLK, hwlib::target::pin_out &OE);
		void setPixel(Vector2i p1, RGB color);
		void recieve_uart();
		void display();
		void clear();
	private:
		hwlib::target::pin_out &LAT, &CLK, &OE;
		hwlib::target::pin_out &A, &B, &C, &D;
		hwlib::target::pin_out &UR, &UG, &UB;
		hwlib::target::pin_out &LR, &LG, &LB;
		
		char buffer1[32][64] = { 0 };
		char buffer2[32][64] = { 0 };
		
		char (*front_buffer)[32][64] = &buffer1;
		char (*back_buffer)[32][64] = &buffer2;
};

#endif
