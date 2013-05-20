/*
 * Planet.cpp
 *
 *  Created on: Apr 18, 2013
 *      Author: LOUISE
 */

#include "Planet.h"

using namespace std;

Planet::Planet(Sprite *sprite, float hitPoints, float x, float y) {
	this->sprite=sprite;
	this->hitPoints=hitPoints;
	this->position.x=x;
	this->position.y=y;
}

Planet::~Planet() {
}
void Planet::render(float cameraX, float cameraY){
	sprite->render(position.x-cameraX,position.y-cameraY);

} /* namespace std */
