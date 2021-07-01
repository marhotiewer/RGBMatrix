#ifndef RGBMATRIX_H
#define RGBMATRIX_H

#include "hwlib.hpp"
#include "datatypes.hpp"

///
/// @brief This class contains all the pins and functions for controlling the matrix.
///
class RGBMatrix {
	public:
		///
		/// @brief All the parameters speak for themselves, they match the naming sceme of the matrix.
		///
		RGBMatrix(hwlib::target::pin_out &A, hwlib::target::pin_out &B, hwlib::target::pin_out &C, hwlib::target::pin_out &D,
				  hwlib::target::pin_out &UR, hwlib::target::pin_out &UG, hwlib::target::pin_out &UB,
				  hwlib::target::pin_out &LR, hwlib::target::pin_out &LG, hwlib::target::pin_out &LB,
				  hwlib::target::pin_out &LAT, hwlib::target::pin_out &CLK, hwlib::target::pin_out &OE);
		///
		/// @brief Sets the specified pixel to the specified colour on the back buffer, wont be drawn on screen yet
		/// @param p1 The point of the pixel.
		/// @param color The colour of the pixel.
		///
		void setPixel(Vector2i p1, RGB color);
		///
		/// @brief This recieves an image from UART, blocking.
		/// @details The images are to be encoded RGB right to left(BGR), using a single bit per channel.
		/// One byte per pixel. The image will be saved in the back buffer. This function is blocking.
		///
		void recieve_uart();
		///
		/// @brief Shifts out the pixels to the matrix from the front buffer, front and back buffer are swapped afterwards.
		///
		void display();
		///
		/// @brief Clears the back buffer, originally used for debugging.
		///
		void clear();
	private:
		hwlib::target::pin_out &LAT, &CLK, &OE;
		hwlib::target::pin_out &A, &B, &C, &D;
		hwlib::target::pin_out &UR, &UG, &UB;
		hwlib::target::pin_out &LR, &LG, &LB;
		///
		/// @brief actual location of the buffer.
		///
		char buffer1[32][64] = { 0 };
		///
		/// @brief actual location of the buffer.
		///
		char buffer2[32][64] = { 0 };
		///
		/// @brief Pointer to the front buffer.
		///
		char (*front_buffer)[32][64] = &buffer1;
		///
		/// @brief Pointer to the back buffer.
		///
		char (*back_buffer)[32][64] = &buffer2;
};

#endif
