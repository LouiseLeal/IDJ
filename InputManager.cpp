/*
 * InputManager.cpp
 *
 *  Created on: May 18, 2013
 *      Author: LOUISE
 */
#define N_KEYS 320
#define N_MOUSE_BUTTONS 7

#include "InputManager.h"
using namespace std;
InputManager* InputManager::instance=0;

InputManager::InputManager(){
	mouseX=mouseY=0;
	quitGame= false;
	teclado=0;
	mouse=0;
}

InputManager* InputManager::getInstance()
{

	if(!instance){
		instance=new InputManager();
	}
	return instance;
}

InputManager::~InputManager(){
	if(NULL!=keyDown){
		delete(keyDown);
	}
	if(NULL!=keyUp){
		delete(keyUp);
	}
	if(NULL!=mouseDown){
		delete(mouseDown);
	}
	if(NULL!=mouseUp){
		delete(mouseUp);
	}

}
void InputManager::Update(){
	SDL_Event event;
	memset(keyDown,(bool)0,sizeof(bool)*N_KEYS);
	memset(keyUp,(bool)0,sizeof(bool)*N_KEYS);
	memset(mouseDown,(bool)0,sizeof(bool)*N_MOUSE_BUTTONS);
	memset(mouseUp,(bool)0,sizeof(bool)*N_MOUSE_BUTTONS);
	SDL_GetMouseState(&mouseX,&mouseY);
	teclado = SDL_GetKeyState(NULL);

	while(SDL_PollEvent(&event))
	{
		switch(event.type){
		case SDL_KEYDOWN:
			keyDown[event.key.keysym.sym]=true;
			break;
		case SDL_KEYUP:
			keyUp[event.key.keysym.sym]=false;
			break;
		case SDL_MOUSEMOTION:
			mouseX=event.motion.x;
			mouseY=event.motion.y;
			break;
		case SDL_MOUSEBUTTONDOWN:
			mouseDown[event.button.button]=true;
			break;
		case SDL_MOUSEBUTTONUP:
			mouseUp[event.button.button]=false;
			break;
		case SDL_QUIT:
			quitGame=true;
			break;
		}
	}
}

bool InputManager::isKeyDown(int key)
{
	return (keyDown[key]);
}
bool InputManager::isKeyUp(int key)
{
	return(keyUp[key]);
}
bool InputManager::isKeyPressed(int key)
{
	if(keyDown[key]) return true;
	return false;
}
bool InputManager::isMouseDown(int button)
{
	return (mouseDown[button]);
}

bool InputManager::isMouseUp(int button)
{
	return (mouseUp[button]);
}
bool InputManager::isMousePressed( Uint8 button ){
	if(mouseDown[button]) return true;
	return false;
}
int InputManager::mousePosX(){
	return mouseX;
}
int InputManager::mousePosY(){
	return mouseY;
}
bool InputManager::isMouseInside(SDL_Rect *rect){
	if(rect->x== mouseX && rect->y==mouseY) return true;
	return false;
}
bool InputManager::QuitGame(){
	return quitGame;
}

