/*
 * GameManager.h
 *
 *  Created on: Apr 13, 2013
 *      Author: LOUISE
 */

#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

//#define DEBUG

#include<stdio.h>
#include<stdlib.h>
#include<SDL/SDL.h>
#include<vector>
#include<iostream>
#include<time.h>
#include"SDLBase.h"
#include"Sprite.h"
#include"Planet.h"
#include"TileMap.h"
#include"TileSet.h"
#include"InputManager.h"


using namespace std;
using std::vector;


class GameManager
{
public:
	/// Atributos
    Sprite* backGround;
    Sprite* planetSprite;

    vector<Planet*> planetArray;

    TileSet *tileset;
    TileMap *tilemap;

    struct Camera{
    	float x;
    	float y;
    }camera;
    struct CameraSpeed{
    	float x;
    	float y;
    }cameraSpeed;

    bool quit;


    /// Métodos
    GameManager();
    virtual ~GameManager();
    void run();
    /// Métodos do Planet
    void addPlanet();
    void checkPlanet();
    void processEvents();
    ///Métodos TileSet , TileMap
    void buildMap();
};

#endif // GAMEMANAGER_H
