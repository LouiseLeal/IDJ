/*
 * InputManager.h
 *
 *  Created on: May 18, 2013
 *      Author: LOUISE
 */

#ifndef INPUTMANAGER_H_
#define INPUTMANAGER_H_

#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include<iostream>
#include "SDL/SDL.h"
#include "Sprite.h"
#include "SDLBase.h"


#define N_KEYS 320
#define N_MOUSE_BUTTONS 7

using namespace std;

class InputManager{
private:
	Uint8 mouse, *teclado;
	bool keyDown[N_KEYS], keyUp[N_KEYS];
	bool mouseDown[N_MOUSE_BUTTONS],mouseUp[N_MOUSE_BUTTONS];
	bool quitGame;
	int mouseX, mouseY;
	static InputManager *instance;
public:

	InputManager();
	virtual ~InputManager();
	InputManager* getInstance();
	void Update();
	bool isKeyDown(int key);
	bool isKeyUp(int key);
	bool isKeyPressed(int key);
	bool isMouseDown(int button);
	bool isMouseUp(int button);
	bool isMousePressed( Uint8 button );
	bool isMouseInside(SDL_Rect *rect);
	int mousePosX();
	int mousePosY();
 	bool QuitGame();


};


#endif /* INPUTMANAGER_H_ */
