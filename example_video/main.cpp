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

	for(;;) {
		matrix.recieve_uart();
		matrix.display();
	}
}
