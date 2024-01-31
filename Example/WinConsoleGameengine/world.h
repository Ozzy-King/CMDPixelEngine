#pragma once
#include "GDISprite.h"

extern int __memused__;

struct vec2d {
	int x=0, y=0;
};

class world {
	enum tileType {
		blank = 0,
		wire = 1,
		grass = 2,
		gravel = 3
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

	int worldOffsetX = -122, worldOffsetY = 100;
	int worldWidth = 10, worldHeight = 10, worldDepth=10;

	int worldLittleTileWidth = 10, worldLittleTileHeight = 10;
	int worldTileWidth = 20, worldTileHeight = 10;

	int*** MAP;

	GDSPsprite worldTileMap;

public:
	vec2d PosToWorldPos(int x, int y, int z){
		vec2d newVec;
		//set along x
		newVec.x = (worldTileWidth/2)*x;
		newVec.y = (worldTileHeight / 2)*x;
		//set along z
		newVec.x -= (worldTileWidth / 2)*z + worldOffsetX;
		newVec.y += (worldTileHeight / 2)*z + worldOffsetY;
		//set along y
		newVec.y -= worldTileHeight * y;
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
	int drawTile(int xTilePos, int yTilePos, int zTilePos) {
		int blockleft = 0, blockright = 0, blockup = 0;
		//check right block
		if (zTilePos < worldDepth-1) {
			blockleft = MAP[yTilePos][zTilePos+1][xTilePos];
		}
		//check left block
		if (xTilePos < worldWidth-1) {
			blockright = MAP[yTilePos][zTilePos][xTilePos+1];
		}
		//check top block
		if (yTilePos < worldHeight - 1) {
			blockup = MAP[yTilePos+1][zTilePos][xTilePos];
		}

		//gridPosToWorldPos
		vec2d worldCoord = PosToWorldPos(xTilePos, yTilePos, zTilePos);

		if (!blockup) {
			//top left
			GDSPdrawSprite(worldCoord.x, worldCoord.y, worldLittleTileWidth, worldLittleTileHeight, &worldTileMap, getTileFromTileMap(Sides::left, (tileType)MAP[yTilePos][zTilePos][xTilePos], tileSection::top));
			//top right
			GDSPdrawSprite(worldCoord.x + worldLittleTileWidth, worldCoord.y, worldLittleTileWidth, worldLittleTileHeight, &worldTileMap, getTileFromTileMap(Sides::right, (tileType)MAP[yTilePos][zTilePos][xTilePos], tileSection::top));
		}
		if (!blockleft) {
			//middle left
			GDSPdrawSprite(worldCoord.x, worldCoord.y + (worldLittleTileHeight / 2), worldLittleTileWidth, worldLittleTileHeight, &worldTileMap, getTileFromTileMap(Sides::left, (tileType)MAP[yTilePos][zTilePos][xTilePos], tileSection::middle));
			//bottom left
			GDSPdrawSprite(worldCoord.x, worldCoord.y + ((worldLittleTileHeight/2)*2), worldLittleTileWidth, worldLittleTileHeight, &worldTileMap, getTileFromTileMap(Sides::left, (tileType)MAP[yTilePos][zTilePos][xTilePos], tileSection::bottom));
		}
			
		if (!blockright) {
			//middle right
			GDSPdrawSprite(worldCoord.x+ worldLittleTileWidth, worldCoord.y + (worldLittleTileHeight / 2), worldLittleTileWidth, worldLittleTileHeight, &worldTileMap, getTileFromTileMap(Sides::right, (tileType)MAP[yTilePos][zTilePos][xTilePos], tileSection::middle));
			//bottom right
			GDSPdrawSprite(worldCoord.x+ worldLittleTileWidth, worldCoord.y + ((worldLittleTileHeight / 2) * 2), worldLittleTileWidth, worldLittleTileHeight, &worldTileMap, getTileFromTileMap(Sides::right, (tileType)MAP[yTilePos][zTilePos][xTilePos], tileSection::bottom));
		}
		return 0;
	}

	int setupMap(int mapWidth, int mapHeight, int mapDepth) {
		//setup map
		MAP = (int***)malloc(sizeof(int**) * mapHeight);
		for (int y = 0; y < mapHeight; y++) {
			MAP[y] = (int**)malloc(sizeof(int*) * mapDepth);
			for (int z = 0; z < mapDepth; z++) {
				MAP[y][z] = (int*)malloc(sizeof(int) * mapDepth);
				for (int x = 0; x < mapWidth; x++) {
					int randy = rand() % 10;
					if (randy < 2) {
						MAP[y][z][x] = 0;
					}
					else if (randy < 6) {
						MAP[y][z][x] = 2;
					}
					else if (randy < 10) {
						MAP[y][z][x] = 3;
					}
				}
			}
		}

		worldHeight = mapHeight;
		worldWidth = mapWidth;
		worldDepth = mapDepth;
		return 0;
	}


	int start() {
		//gets the tile map
		char WorldTileMap[] = "./isometricWorldTileMap.bmp";
		this->worldTileMap = GDSPcreateSprite(WorldTileMap, 200, 100, 10, 10, 1, RGB(255, 255, 255));

		//setup map
		setupMap(10,10, 10);

		return 0;
	}

	int update() {
		
		for (int y = 0; y < worldHeight; y++) {
			for (int z = 0; z < worldDepth; z++) {
				std::thread xthread = std::thread([&]() {
					for (int x = 0; x < worldWidth; x++) {
						drawTile(x, y, z);
					}
				});
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