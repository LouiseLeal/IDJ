/*
 * main.cpp
 *
 *  Created on: Apr 13, 2013
 *      Author: LOUISE
 */
#include <cstdlib>
#include"GameManager.h"
#include<iostream>
using namespace std;




int main(int argc, char *argv[])
{
	//Seed para os numeros alatórios
	srand((unsigned)time(NULL));

	//Cria objeto GameManager
    GameManager objGameManager;

    //Roda loop principal do jogo
    objGameManager.run();

    return 0;
}




