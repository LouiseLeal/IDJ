/*
 * TileMap.cpp
 *
 *  Created on: May 11, 2013
 *      Author: LOUISE
 */

#include "TileMap.h"

using namespace std;
TileMap::TileMap(int width, int height, int tileSize, int layer , TileSet* tilesetMap){

	this->mapWidth=width;
	this->mapHeight=height;
	this->mapLayer=layer;
	this->tilesetMap=tilesetMap;

	tileMap.assign(mapWidth,std::vector< std::vector<int> >(mapHeight, std::vector<int>(mapLayer,-1)));

	for(unsigned int i = 0; i< tileMap.size(); ++i){
		for(unsigned int j = 0;j < tileMap[0].size(); ++j){
			for(unsigned int z = 0;z < tileMap[0][0].size(); ++z){
				tileMap[i][j][z]=-1;
			}
		}
	}
}
//TileMap::TileMap(std::string mapa, TileSet* tileset){
//	this->mapHeight=0;
//	this->mapLayer=0;
//	this->mapWidht=0;
//	this->tileset=tileset;
//	load(mapa);
//}

//void TileMap::load(string mapPath){
//
//}
TileMap::~TileMap(){

 }

void TileMap::setTileSet(TileSet* tilesetMap){
	this->tilesetMap=tilesetMap;
}

int& TileMap::at(int x, int y, int z){
	return  tileMap[x][y][z];
}

void TileMap::render(float cameraX, float cameraY){
	int index;
	if(!tilesetMap->usingSingleFile()){
			for(unsigned int i = 0; i< tileMap.size(); ++i){
				for(unsigned int j = 0;j < tileMap[0].size(); ++j){
					for(unsigned int z=0; z < tileMap[0][0].size(); z++){
						if(tileMap[i][j][z] >= 0){
							index = tileMap[i][j][z];
							int posx , posy;
							posx = tilesetMap->getTileWidth()*i;
							posy = tilesetMap->getTileHeight()*j;
							
							tilesetMap->render(index,(posx - cameraX), (posy - cameraY));
					}
				}

			}
		}
	}
}

//void rederLayer(float cameraX, float cameraY, int layer){
//}

int TileMap::getWidth(){
return this->mapWidth ;
}

int TileMap::getHeight(){
return this->mapHeight ;
}

int TileMap::getLayer(){
return this->mapLayer ;
}
