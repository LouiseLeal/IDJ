/*
 * Planet.h
 *
 *  Created on: Apr 18, 2013
 *      Author: LOUISE
 */

#ifndef PLANET_H
#define PLANET_H

#include<stdio.h>
#include<stdlib.h>
#include"SDL/SDL.h"
#include<SDL/SDL_image.h>
#include<iostream>
#include "Sprite.h"
#include "SDLBase.h"

using namespace std;

class Planet {
public:

	Sprite *sprite;
	struct Position {
		float x;
		float y;
	} position;
	float hitPoints;

	Planet(Sprite *sprite, float hitPoints, float x, float y);
	virtual ~Planet();
	void render(float cameraX, float cameraY);
};

#endif /* PLANET_H_ */
