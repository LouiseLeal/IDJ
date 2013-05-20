/*
 * TileMap.h
 *
 *  Created on: May 11, 2013
 *      Author: LOUISE
 */

#ifndef TILEMAP_H
#define TILEMAP_H

#include<stdio.h>
#include<stdlib.h>
#include<SDL/SDL.h>
#include<vector>
#include<iostream>
#include<time.h>
#include"SDLBase.h"
#include"Sprite.h"
#include"TileSet.h"


using namespace std;


class TileMap
{
public:
	/// Atributos
    vector<vector<vector<int> > > tileMap;
	TileSet * tilesetMap;
    int mapWidth, mapHeight, mapLayer;


	///Métodos
    TileMap(int mapWidth, int mapheight, int tileSize, int layer =1, TileSet* tileset =NULL);
    TileMap(string mapa, TileSet* tileset=NULL);
    virtual ~TileMap();
	void load(string mapPath);
	void setTileSet(TileSet* tileset);
    int& at(int x, int y, int z=0);
	void render(float cameraX= 0.0, float cameraY=0.0);
	int getWidth();
	int getHeight();
	int getLayer();

};


#endif /* TILEMAP_H */
