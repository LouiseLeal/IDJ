/*
 * Sprite.h
 *
 *  Created on: Apr 13, 2013
 *      Author: LOUISE
 */

#ifndef SPRITE_H
#define SPRITE_H

#include<stdio.h>
#include<stdlib.h>
#include<SDL/SDL.h>
#include<SDL/SDL_image.h>
#include<iostream>
#include"SDLBase.h"

class Sprite
{
public:
    /// Atributos
    SDL_Surface* surface;
    SDL_Rect clipRect;
    SDLBase objSDLBase;

    /// Métodos
    Sprite(std::string arquivo);
    virtual ~Sprite();
    void load(std::string arquivo);
    void clip(int x, int y, int w, int h);
    SDL_Rect getClip();
    int getWidth();
    int getHeight();
    void render(int x, int y);
};

#endif // SPRITE_H
