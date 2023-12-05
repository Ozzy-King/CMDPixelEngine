#include "GDISprite.h"

struct GDSPsprite GDSPcreateSprite(char* fileName, int imgWidth, int imgHeight, int tileWidth, int tileHeight, int transparent , COLORREF transparentColour) {
	struct GDSPsprite newSprite;
	newSprite._tileWidth = tileWidth;
	newSprite._tileHeight = tileHeight;
	newSprite._transparent = transparent;
	newSprite._transparentColour = transparentColour;

	//gets sprite into the GDSPsprite
	//gets the lenght of the filename string and converts to wide char array
	int filenameLen = 0;
	while (fileName[filenameLen] != '\0') { filenameLen++; }
	
	WCHAR* ConvertedFilename = (WCHAR*)malloc(sizeof(WCHAR) * (filenameLen+1));
	for (int i = 0; i < filenameLen; i++) { ConvertedFilename[i] = fileName[i]; } 
	ConvertedFilename[filenameLen] = '\0';

	newSprite._spriteMap = (HBITMAP)LoadImage(NULL, ConvertedFilename, IMAGE_BITMAP, imgWidth, imgHeight, LR_LOADFROMFILE);

	//get all the tiles
	int numberOfTiles = (imgWidth / tileWidth) * (imgHeight / tileHeight);//gets number of tiles (will be used later to index arrays)
	newSprite._numberOfTiles = numberOfTiles;//saves for later reference
	newSprite._topLeftX = (int*)malloc(sizeof(int) * numberOfTiles); //allocations space for array
	newSprite._topLeftY = (int*)malloc(sizeof(int) * numberOfTiles); // ditto above
	for (int y = (imgHeight- tileHeight); y >= 0; y -= tileHeight) {
		for (int x = (imgWidth-tileWidth); x >= 0; x -= tileWidth) {
			numberOfTiles--;
			newSprite._topLeftX[numberOfTiles] = x;
			newSprite._topLeftX[numberOfTiles] = y;
		}
	}

	free(ConvertedFilename);
	return newSprite;
}