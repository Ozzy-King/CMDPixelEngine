#pragma once
#include "GDISprite.h"

struct vec2d {
	int x, y;
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
	int worldWidth = 0, worldHeight = 0;

	int worldLittleTileWidth = 10, worldLittleTileWidth = 10;
	int worldTileWidth = 20, worldTileHeight = 10;

	int** MAP;

	GDSPsprite worldTileMap;

public:
	vec2d PosToWorldPos(int x, int y){
		vec2d newVec;
		//set along x
		newVec.x += (worldTileWidth/2)*x;
		newVec.y += (worldTileHeight / 2)*x;
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
	int drawTile(int xTilePos, int yTilePos) {
		int blockleft = 0, blockright = 0;
		//check left block
		if (xTilePos > 0 || xTilePos < worldWidth) {
		
		}
		if (yTilePos > 0 || yTilePos < worldHeight) {

		}


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
				MAP[y][x] = tileType::blank;
			}
		}

		return 0;
	}

	int update() {
		
		for (int y = 0; y < worldHeight; y++) {
			int worldY = tileYToWorld(y);
			for (int x = 0; x < worldWidth; x++) {
				int worldX = tileXToWorld(x);
				//GDSPdrawSprite();
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