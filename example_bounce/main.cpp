#include "hwlib.hpp"

#include "../RGBMatrix/RGBMatrix.h"
#include "../RGBMatrix/Rectangle.h"
#include "../RGBMatrix/Circle.h"
#include "../RGBMatrix/Line.h"

int main() {
	// wait for UART to be ready
	hwlib::wait_ms(250);
	hwlib::cout << "DEBUGGING TEST\n";

	hwlib::target::pin_out A(hwlib::target::pins::d41);
	hwlib::target::pin_out B(hwlib::target::pins::d40);
	hwlib::target::pin_out C(hwlib::target::pins::d39);
	hwlib::target::pin_out D(hwlib::target::pins::d38);
	
	hwlib::target::pin_out UR(hwlib::target::pins::d51);
	hwlib::target::pin_out UG(hwlib::target::pins::d49);
	hwlib::target::pin_out UB(hwlib::target::pins::d47);
	
	hwlib::target::pin_out LR(hwlib::target::pins::d50);
	hwlib::target::pin_out LG(hwlib::target::pins::d48);
	hwlib::target::pin_out LB(hwlib::target::pins::d46);
	
	hwlib::target::pin_out LAT(hwlib::target::pins::d37);
	hwlib::target::pin_out CLK(hwlib::target::pins::d36);
	hwlib::target::pin_out OE(hwlib::target::pins::d35);

	RGBMatrix matrix(A, B, C, D, UR, UG, UB, LR, LG, LB, LAT, CLK, OE);

	Circle big = Circle(Vector2i(20, 15), 10, RGB(0, 0, 1), true);
	Circle medium = Circle(Vector2i(10, 10), 5, RGB(0, 1, 0), false);
	Circle tiny = Circle(Vector2i(57, 28), 0, RGB(1, 0, 0), false);

	Drawable* objects[] = {
		&big,
		&medium,
		&tiny
	};

	uint_fast64_t start = hwlib::now_us();

	for(;;) {

		if(hwlib::now_us() - start > 50000) {
			start = hwlib::now_us();
			for (uint32_t i = 0; i < 3; i++)
				objects[i]->update();
		}
		matrix.clear();
		for (uint32_t i = 0; i < 3; i++)
			objects[i]->draw(matrix);
		matrix.display();
	}
}
