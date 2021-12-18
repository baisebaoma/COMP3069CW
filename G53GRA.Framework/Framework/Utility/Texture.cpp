#include "Texture.h"

#ifdef _WIN32
#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#else
#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>
#pragma pack(1)
#define WORD unsigned short
#define DWORD unsigned int
#define LONG int
typedef struct tagBITMAPFILEHEADER
{
	WORD  bfType;
	DWORD bfSize;
	WORD  bfReserved1;
	WORD  bfReserved2;
	DWORD bfOffBits;
} BITMAPFILEHEADER, *PBITMAPFILEHEADER;
typedef struct tagBITMAPINFOHEADER
{
	DWORD biSize;
	LONG biWidth;
	LONG biHeight;
	WORD biPlanes;
	WORD biBitCount;
	DWORD biCompression;
	DWORD biSizeImage;
	LONG biXPelsPerMeter;
	LONG biYPelsPerMeter;
	DWORD biClrUsed;
	DWORD biClrImportant;
} BITMAPINFOHEADER;
#endif

#include <iostream>

using namespace std;

Texture::~Texture(void)
{
	GLuint t;
	// free up all the textures
	for (map<int, string>::iterator it = textures.begin(); it != textures.end(); ++it)
	{
		t = static_cast<GLuint>(it->first);
		glDeleteTextures(static_cast<GLsizei>(1), &t);
	}
}

// Loads a bitmap into texture memory
int Texture::GetTexture(string fileName)
{
	for (map<int, string>::iterator ii = textures.begin(); ii != textures.end(); ++ii)
	{
		if (ii->second == fileName)
		{
			return ii->first;
		}
	}

	BITMAPFILEHEADER fileHeader;
	BITMAPINFOHEADER infoHeader;
	unsigned char *pixelBuffer;
	GLuint texObject;
	FILE *bitmapFile = fopen(fileName.c_str(), "r");

	// Check file opened
	if (bitmapFile == NULL)
	{
		printf("Error: Failed to open the file at path %s\n", fileName.c_str());
		delete[] bitmapFile;
		return -1;	// error
	}
	fread(&fileHeader, 14, 1, bitmapFile);

	// Check for valid window bitmap
	if (fileHeader.bfType != 0x4D42)
	{
		printf("Error: Trying to load %s it is in an invalid bitmap format.\n", fileName.c_str());
		fclose(bitmapFile);
		return -1;	// error
	}

	// read in file header
	fread(&infoHeader, sizeof(BITMAPINFOHEADER), 1, bitmapFile);

	// Check the image is at least RGB ... i.e 24 bits per pixel
	if (infoHeader.biBitCount < 24)
	{
		printf("Error: Trying to load %s.\nThe file is not in RGB or RGBA format.\nIt may be in grayscale format, open it in an image editor of your choice and change the image mode to RGB or RGBA.\n", fileName.c_str());
		fclose(bitmapFile);
		return -1;	// error
	}
    
    printf("%s's bitcount is: %d\n", fileName.c_str(), infoHeader.biBitCount);

	// ofset the pointer to the start of the pixel data
	fseek(bitmapFile, fileHeader.bfOffBits, SEEK_SET);

	// Read in the pixel data
	pixelBuffer = new unsigned char[infoHeader.biWidth * infoHeader.biHeight * (infoHeader.biBitCount / 8)];  // 这里读进去透明度了没有？
	fread(pixelBuffer, sizeof(unsigned char), infoHeader.biWidth * infoHeader.biHeight * (infoHeader.biBitCount / 8), bitmapFile);

	// If texture is in ABGR format swizzle it into RGBA for openGL upload
	if (infoHeader.biBitCount == 32)
	{
		unsigned char c;
		for (int i = 0; i < infoHeader.biWidth * infoHeader.biHeight; i++)  // 对每一个像素，做这个事情：
		{
			c = pixelBuffer[i * 4];
			pixelBuffer[i * 4] = pixelBuffer[i * 4 + 3];
			pixelBuffer[i * 4 + 3] = c;
			c = pixelBuffer[i * 4 + 1];
			pixelBuffer[i * 4 + 1] = pixelBuffer[i * 4 + 2];
			pixelBuffer[i * 4 + 2] = c;
		}
	}

	// Enable texturing
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);

	// Generate a texture buffer
	glGenTextures(static_cast<GLsizei>(1), &texObject);

	// Bin to buffer
	glBindTexture(GL_TEXTURE_2D, texObject);

	// Set texture parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// Upload texture data
	glTexImage2D(GL_TEXTURE_2D, static_cast<GLint>(0), infoHeader.biBitCount == 32 ? GL_RGBA : GL_RGB,  // 如果是32位，那么就说他是RGBA。如果不是那就是RGB。
		static_cast<GLsizei>(infoHeader.biWidth), static_cast<GLsizei>(infoHeader.biHeight),
		static_cast<GLint>(0), infoHeader.biBitCount == 32 ? GL_RGBA : GL_BGR_EXT, GL_UNSIGNED_BYTE,  // 如果是32为就是RGBA，不是就是BGR
		static_cast<GLvoid*>(pixelBuffer));

	// insert texture into texture list
	textures.insert(textures.end(), pair<int, string>(static_cast<int>(texObject), fileName));

	// Delete old copy of pixel data
	delete[] pixelBuffer;
	fclose(bitmapFile);
	glDisable(GL_TEXTURE_2D);

	return static_cast<int>(texObject);
}
