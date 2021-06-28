#include "RGBMatrix.h"

RGBMatrix::RGBMatrix(hwlib::target::pin_out &A, hwlib::target::pin_out &B, hwlib::target::pin_out &C, hwlib::target::pin_out &D,
					 hwlib::target::pin_out &UR, hwlib::target::pin_out &UG, hwlib::target::pin_out &UB,
		  			 hwlib::target::pin_out &LR, hwlib::target::pin_out &LG, hwlib::target::pin_out &LB,
		  			 hwlib::target::pin_out &LAT, hwlib::target::pin_out &CLK, hwlib::target::pin_out &OE):
	LAT(LAT), CLK(CLK), OE(OE),
	A(A), B(B), C(C), D(D),
	UR(UR), UG(UG), UB(UB),
	LR(LR), LG(LG), LB(LB)
{
	OE.write(1);
}

void RGBMatrix::recieve_uart() {
	hwlib::uart_putc((char)1);
	for(int x = 0; x < 32; x++) {
		for(int y = 0; y < 64; y++) {
			(*back_buffer)[x][y] = hwlib::uart_getc();
		}
	}
}

void RGBMatrix::display() {
	for(int s = 0; s < 16; s++) {
		D.write((s>>3)&1);
		C.write((s>>2)&1);
		B.write((s>>1)&1);
		A.write((s>>0)&1);
		
		for(int p = 0; p < 64; p++) {
			UR.write(((*front_buffer)[s][p]>>0)&1);
			UG.write(((*front_buffer)[s][p]>>1)&1);
			UB.write(((*front_buffer)[s][p]>>2)&1);

			LR.write(((*front_buffer)[s+16][p]>>0)&1);
			LG.write(((*front_buffer)[s+16][p]>>1)&1);
			LB.write(((*front_buffer)[s+16][p]>>2)&1);
			
			CLK.write(1);
			CLK.write(0);
		}
		LAT.write(1);
		LAT.write(0);
		
		OE.write(0);
		hwlib::wait_us(50);
		OE.write(1);
	}
	auto f_buff = front_buffer;
	front_buffer = back_buffer;
	back_buffer = f_buff;
}

void RGBMatrix::setPixel(Vector2i p1, RGB color) {
	if(p1 <= Vector2i(64, 32) && p1 >= Vector2i(1, 1)) {
		(*back_buffer)[p1.y-1][p1.x-1] = color.color_code;
	}
}

void RGBMatrix::clear() {
	for(int y = 0; y < 32; y++) {
		for(int x = 0; x < 64; x++) {
			(*back_buffer)[y][x] = 0x00;
		}
	}
}
