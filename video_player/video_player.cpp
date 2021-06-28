#include <windows.h>
#include <iostream>
#include <cstdint>
#include <fstream>

#pragma pack(push, 1)
struct mBITMAPFILEHEADER {
	uint16_t file_type;		// the header field used to identify the BMP and DIB file is 0x42 0x4D in hexadecimal, same as BM in ASCII
	uint32_t file_size;		// the size of the BMP file in bytes
	uint16_t reserved1;		// reserved; actual value depends on the application that creates the image, if created manually can be 0
	uint16_t reserved2;		// reserved; actual value depends on the application that creates the image, if created manually can be 0
	uint32_t offset_data;	// the offset, i.e. starting address, of the byte where the bitmap image data (pixel array) can be found
};
struct mBITMAPINFOHEADER {
	uint32_t size;					// the size of this header, in bytes (40)
	int32_t  width;					// the bitmap width in pixels (signed integer)
	int32_t  height;				// the bitmap height in pixels (signed integer)
	uint16_t planes;				// the number of color planes (must be 1)
	uint16_t bit_count;				// the number of bits per pixel, which is the color depth of the image. Typical values are 1, 4, 8, 16, 24 and 32
	uint32_t compression;			// the compression method being used
	uint32_t size_image;			// the image size. This is the size of the raw bitmap data; a dummy 0 can be given for BI_RGB bitmaps
	int32_t  x_pixels_per_meter;	// the horizontal resolution of the image. (pixel per metre, signed integer)
	int32_t  y_pixels_per_meter;	// the vertical resolution of the image. (pixel per metre, signed integer)
	uint32_t colors_used;			// the number of colors in the color palette, or 0 to default to 2n
	uint32_t colors_important;		// the number of important colors used, or 0 when every color is important; generally ignored
};
#pragma pack(pop)

void decode(const char* path, uint8_t data[][64]) {
	std::ifstream bmp("frames\\" + std::string(path), std::ios_base::binary);
	
	uint8_t header[sizeof(mBITMAPFILEHEADER)+sizeof(mBITMAPINFOHEADER)];
	bmp.read((char*)header, sizeof(BITMAPFILEHEADER)+sizeof(mBITMAPINFOHEADER));
	
	mBITMAPFILEHEADER *file_hdr = (mBITMAPFILEHEADER*)&header;
	mBITMAPINFOHEADER *info_hdr = (mBITMAPINFOHEADER*)&header[sizeof(mBITMAPFILEHEADER)];
	
	uint8_t* image = new uint8_t[info_hdr->size_image];
	bmp.seekg(file_hdr->offset_data);
	bmp.read((char*)image, info_hdr->size_image);
	
	for(int j = 0; j < info_hdr->height; j++) {
		for(int i = 0; i < info_hdr->width; i++) {
			data[j][i] = (image[(j-(info_hdr->height-1))*-1*info_hdr->width/8+info_hdr->width/8%4+i/8]&0x80>>i%8)?7:0;
		}
	}
	delete[] image;
}

int main(int argc, char* argv[]) {
	HANDLE hComm = CreateFileA("\\\\.\\COM4", GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);

	if (hComm == INVALID_HANDLE_VALUE) {
		printf("error in opening serial port\n");
		return 1;
	}

	uint8_t image[32][64];
	uint8_t character = 0;
	long unsigned int numberOfBytesRead = 0;
	long unsigned int numberOfBytesWritten = 0;

	WIN32_FIND_DATA file_data;
	HANDLE hFind = FindFirstFile("frames\\*.bmp", &file_data);
	do {
		decode(file_data.cFileName, image);
		while (character != 1) {
			ReadFile(hComm, &character, 1, &numberOfBytesRead, NULL);
		} character = 0;
		WriteFile(hComm, &image[0][0], 2048, &numberOfBytesWritten, NULL);
	} while (FindNextFile(hFind, &file_data) != 0);
	FindClose(hFind);
	return 0;
}
