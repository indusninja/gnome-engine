// Texture.h : Data Structure to hold texture data and method to load a Targa texture.

// Thanks for code sample from Ronny André Reierstad at www.morrowland.com and 
// Ben Humphrey at Game Tutorials for his OpenGL image loading code. 

#ifndef __Texture_H
#define __Texture_H

#define TGA_RGB		 2
#define TGA_A		 3
#define TGA_RLE		10

struct TargaImage
{
	int channels;
	int sizeX;
	int sizeY;
	unsigned char *data;
};

bool Load_Texture(UINT &texture, LPSTR strFileName);

TargaImage *LoadTGA(const char *strFileName);

#endif
