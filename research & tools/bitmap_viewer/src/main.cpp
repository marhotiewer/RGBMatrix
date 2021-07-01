#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstdint>
#include <fstream>

#pragma pack(push, 1)
struct BITMAPFILEHEADER {
	uint16_t file_type;		// the header field used to identify the BMP and DIB file is 0x42 0x4D in hexadecimal, same as BM in ASCII
	uint32_t file_size;		// the size of the BMP file in bytes
	uint16_t reserved1;		// reserved; actual value depends on the application that creates the image, if created manually can be 0
	uint16_t reserved2;		// reserved; actual value depends on the application that creates the image, if created manually can be 0
	uint32_t offset_data;	// the offset, i.e. starting address, of the byte where the bitmap image data (pixel array) can be found
};
struct BITMAPINFOHEADER {
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

// currently only handles uncompressed 24 bit color depth bitmaps
int main(int argc, char* argv[]) {
	std::ifstream bmp(argv[1], std::ios_base::binary);
	
	char header[sizeof(BITMAPFILEHEADER)+sizeof(BITMAPINFOHEADER)];
	bmp.read(header, sizeof(BITMAPFILEHEADER)+sizeof(BITMAPINFOHEADER));
	
	BITMAPFILEHEADER *file_hdr = (BITMAPFILEHEADER*)&header;
	BITMAPINFOHEADER *info_hdr = (BITMAPINFOHEADER*)&header[sizeof(BITMAPFILEHEADER)];
	
	char* image = new char[info_hdr->size_image];
	bmp.seekg(file_hdr->offset_data);
	bmp.read(image, info_hdr->size_image);

	int32_t bytes_per_pixel = info_hdr->bit_count / 8;
	int32_t padding = (4 - (info_hdr->width * bytes_per_pixel) % 4) % 4;
	int32_t bytes_per_line = (info_hdr->width * bytes_per_pixel) + padding;
	
    sf::RenderWindow window(sf::VideoMode(info_hdr->width, info_hdr->height), "BMP Viewer", sf::Style::Titlebar | sf::Style::Close);
	
	sf::VertexArray img(sf::Points);
	for(int i = info_hdr->size_image - bytes_per_line; i >= 0; i -= bytes_per_line) {
		int y = (int(i / bytes_per_line) - ((info_hdr->size_image - bytes_per_line) / bytes_per_line)) * -1;
		for(int j = i; j < (i + bytes_per_line) - bytes_per_pixel; j += bytes_per_pixel) {
			img.append(sf::Vertex(sf::Vector2f((j-i) / bytes_per_pixel, y + 1), sf::Color(image[j+2] / 16, image[j+1] / 16, image[j] / 16)));
		}
	}

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event))
            if (event.type == sf::Event::Closed)
                window.close();
		
        window.clear(sf::Color::Red);
		window.draw(img);
        window.display();
    }
	delete[] image;
    return 0;
}
