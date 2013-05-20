/*
 * Sprite.cpp
 *
 *  Created on: Apr 13, 2013
 *      Author: LOUISE
 */
#include "Sprite.h"
#include"SDLBase.h"

using namespace std;

Sprite::Sprite(string arquivo)
{
   surface=NULL;
   load(arquivo);
}
Sprite::~Sprite(){

    if(surface!=NULL){
        SDL_FreeSurface(surface);
    }
}
/*
 * load(string): verifica se a surface esta descarregada,
 * em seguida carrega surface
 */
void Sprite::load(std::string arquivo){
    if(surface!=NULL){
        SDL_FreeSurface(surface);
    }
    surface=SDLBase::loadImage(arquivo);
    clipRect.x=0;
    clipRect.y=0;
    clipRect.w=surface->w;
    clipRect.h=surface->w;
}
/*
 * clip(int,int,int,int):define os parametros do retangulo clipRect
 */
void Sprite::clip(int x, int y, int w, int h){
    clipRect.x=x;
    clipRect.y=y;
    clipRect.w=w;
    clipRect.h=h;
}
/*
 * getClip(): retorna o retangulo clipRect;
 */
SDL_Rect Sprite::getClip(){
    return clipRect;
}
/*
 *render(x,y): renderiza a surface na posiçãpo
 *parametros x e y.
 */
void Sprite::render(int x, int y){
    SDL_Rect dst;
    dst.x=x;
    dst.y=y;
    dst.w=0;
    dst.h=0;

    SDLBase::renderSurface(surface,&clipRect,&dst);
}
/*
 * getWidth():retorna parametro SDL_Rect->w,
 * do surface
 */
int Sprite::getWidth(){
    return surface->w;
}
/*
* getHeight():retorna parametro SDL_Rect->h,
* do surface.
*/
int Sprite::getHeight(){
    return surface->h;
}
