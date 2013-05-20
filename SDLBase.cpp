/*
 * SDLBase.cpp
 *
 *  Created on: Apr 13, 2013
 *      Author: LOUISE
 */

#include"SDLBase.h"
#include<stdio.h>
#include<stdlib.h>
#include"SDL/SDL.h"
#include<SDL/SDL_image.h>
#include<iostream>

SDL_Surface* SDLBase::screen=0;

using namespace std;

SDLBase::SDLBase()
{
}
/*
 * inicializaSDL(): Inicializa recursos da SDL;
 * inicializa screen;
 */
int SDLBase::inicializaSDL()
{
    if(SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO | SDL_INIT_TIMER)==-1) {
        cout<<"Problema na inicializacao do SDL!"<<endl<<SDL_GetError()<<endl;
        return 0;
    }
    screen = SDL_SetVideoMode(800,600,32,SDL_SWSURFACE);
    if(screen == NULL)
    	return 0;
    SDL_WM_SetCaption("Exercicio2 090121970", "Exercicio1 090121970");
    return  1;
}

/*
 * getScreen():retorna a screen;
 */
SDL_Surface* SDLBase::getScreen()
{
    return screen;
}
/*
 * loadImage(string): nome do arquivo
 * carrega uma nova imagem , surface.
 */
SDL_Surface* SDLBase::loadImage(std::string arquivo)
{

    SDL_Surface* surface=NULL;
    SDL_Surface* surf=NULL;
    surf = IMG_Load(arquivo.c_str());
    if(surf->format->Amask){
        surface=SDL_DisplayFormatAlpha(surf);
    }else{
		surface=SDL_DisplayFormat(surf);
	}	
    
    SDL_FreeSurface(surf);
    return surface;
}
/*
 * renderSurface(SDL_Surface*,SDL_Rect*,SDL_Rect*)
 * renderiza com novas informações a surface na tela.
 */
void SDLBase::renderSurface(SDL_Surface* surface, SDL_Rect* clip, SDL_Rect* dist)
{
    SDL_BlitSurface(surface,clip,screen,dist);
}
/*
 * atualizaTela():atualiza todas as modificações feitas
 * na tela.
 */
void SDLBase::atualizaTela()
{
    SDL_Flip(screen);
}
