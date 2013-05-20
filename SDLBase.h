/*
 * SDLBase.h
 *
 *  Created on: Apr 13, 2013
 *      Author: LOUISE
 */

#ifndef SDLBASE_H_
#define SDLBASE_H_

#include<stdio.h>
#include<stdlib.h>
#include"SDL/SDL.h"
#include<SDL/SDL_image.h>
#include<iostream>

using namespace std;

class SDLBase {
public:

	/// Atributos
	static SDL_Surface* screen;

	/// Métodos
	SDLBase();
	static	int inicializaSDL();
	SDL_Surface* getScreen();
	static SDL_Surface* loadImage(std::string arquivo);
	static void renderSurface(SDL_Surface* surface, SDL_Rect* clip = NULL, SDL_Rect* dist=NULL);
	static void atualizaTela();
};

#endif /* SDLBASE_H_ */
