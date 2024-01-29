#pragma once
#include "GDISprite.h"

struct vec2d {
	int x=0, y=0;
};

class world {
	enum tileType {
		blank = 0,
		grass = 1,
		gravel = 2
	};
	enum tileSection {
		top = 0,
		middle,
		bottom

	};
	enum Sides {
		left = 0,
		right
	};

	int worldOffsetX = 0, worldOffsetY = 0;
	int worldWidth = 10, worldHeight = 10;

	int worldLittleTileWidth = 10, worldLittleTileHeight = 10;
	int worldTileWidth = 20, worldTileHeight = 10;

	int** MAP;

	GDSPsprite worldTileMap;

public:
	vec2d PosToWorldPos(int x, int y){
		vec2d newVec;
		//set along x
		newVec.x = (worldTileWidth/2)*x;
		newVec.y = (worldTileHeight / 2)*x;
		//set along y
		newVec.x -= (worldTileWidth / 2)*y;
		newVec.y += (worldTileHeight / 2)*y;
		return newVec;
	}
	int getTileFromTileMap(Sides side, tileType tiletype, tileSection tilesect) {
		int tileMapSelect = 0;
		//if 0 .. 2 .. 4.. 6 - get left handtile
		if (!side) {
			tileMapSelect = 0;
		}
		else { tileMapSelect = 1; }

		tileMapSelect += tiletype * 2; //goes to the correct tile type
		tileMapSelect += tilesect * 20; //goes to the correct tile section
		return tileMapSelect;
	}
	//TODO correc tthe check for if the side should draw
	int drawTile(int xTilePos, int yTilePos) {
		int blockleft = 0, blockright = 0;
		//check right block
		if (xTilePos < worldWidth) {
			blockright = MAP[yTilePos][xTilePos+1];
		}
		//check left block
		if (yTilePos > 0) {
			blockright = MAP[yTilePos-1][xTilePos];
		}
		//gridPosToWorldPos
		vec2d worldCoord = PosToWorldPos(xTilePos, yTilePos);
		//top left
		GDSPdrawSprite(worldCoord.x, worldCoord.y, worldLittleTileWidth, worldLittleTileHeight, &worldTileMap, getTileFromTileMap(Sides::left, (tileType)MAP[yTilePos][xTilePos], tileSection::top));
		//top right
		GDSPdrawSprite(worldCoord.x+ worldLittleTileWidth, worldCoord.y, worldLittleTileWidth, worldLittleTileHeight, &worldTileMap, getTileFromTileMap(Sides::right, (tileType)MAP[yTilePos][xTilePos], tileSection::top));
		
		if (!blockleft) {
				//middle left
				GDSPdrawSprite(worldCoord.x, worldCoord.y + (worldLittleTileHeight / 2), worldLittleTileWidth, worldLittleTileHeight, &worldTileMap, getTileFromTileMap(Sides::left, (tileType)MAP[yTilePos][xTilePos], tileSection::middle));
				//bottom left
				GDSPdrawSprite(worldCoord.x, worldCoord.y + ((worldLittleTileHeight/2)*2), worldLittleTileWidth, worldLittleTileHeight, &worldTileMap, getTileFromTileMap(Sides::left, (tileType)MAP[yTilePos][xTilePos], tileSection::bottom));
		}
			
		if (!blockright) {
				//middle right
				GDSPdrawSprite(worldCoord.x+ worldLittleTileWidth, worldCoord.y + (worldLittleTileHeight / 2), worldLittleTileWidth, worldLittleTileHeight, &worldTileMap, getTileFromTileMap(Sides::right, (tileType)MAP[yTilePos][xTilePos], tileSection::middle));
				//bottom right
				GDSPdrawSprite(worldCoord.x+ worldLittleTileWidth, worldCoord.y + ((worldLittleTileHeight / 2) * 2), worldLittleTileWidth, worldLittleTileHeight, &worldTileMap, getTileFromTileMap(Sides::right, (tileType)MAP[yTilePos][xTilePos], tileSection::bottom));
		}
		return 0;
	}

	int start() {
		//gets the tile map
		char WorldTileMap[] = "./isometricWorldTileMap.bmp";
		this->worldTileMap = GDSPcreateSprite(WorldTileMap, 200, 100, 10, 10, 1, RGB(255, 255, 255));

		//setup map
		MAP = (int**)malloc(sizeof(int*) * worldHeight);
		for (int y = 0; y < worldHeight; y++) {
			MAP[y] = (int*)malloc(sizeof(int) * worldWidth);
			for (int x = 0; x < worldWidth; x++) {
				MAP[y][x] = tileType::grass;
			}
		}

		return 0;
	}

	int update() {
		
		for (int y = 0; y < worldHeight; y++) {
			for (int x = 0; x < worldWidth; x++) {
				drawTile(x, y);
			}
		}
		

		return 0;
	}

	int destory() {
		for (int y = 0; y < worldHeight; y++) {
			free(MAP[y]);
		}
		free(MAP);


		return 0;
	}

};