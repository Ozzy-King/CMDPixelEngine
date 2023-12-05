#ifndef GDISPRITE__
#define GDISPRITE__
#include <Windows.h>

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

	//structure to hold the bitmap sprite map
	struct GDSPsprite {
		HBITMAP _spriteMap;

		COLORREF _transparentColour;
		int _transparent;
		
		int* _topLeftX;
		int* _topLeftY;
		int _tileWidth;
		int _tileHeight;
		int _numberOfTiles;
	};

	//GDI SPRITE creation function (each sprite tile must be same width and height)
	struct GDSPsprite GDSPcreateSprite(char* fileName, int imgWidth, int imgHeight, int tileWidth, int tileHeight, int transparent , COLORREF transparentColour);










#ifdef __cplusplus
}
#endif // __cplusplus


#endif