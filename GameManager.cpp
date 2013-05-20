/*
 * GameManager.cpp
 *
 *  Created on: Apr 13, 2013
 *      Author: LOUISE
 */

#include "GameManager.h"

#define SCROLL 20.0f
#define TILEMAP_SIZE 16
#define TILE_SIZE 75
#define N_TEXTURES 30
#define IMAGEM_BACK_GROUND "img/fundo.png"
#define IMAGEM_PLANETA "img/PlanetaVermelho.png"
#define IMAGEM_SPACETILE "img/tileset/SpaceTile-01.png"


using namespace std;
using std::vector;
/*
 *Construtor: Inializa SDL e Sprites;*
 */
GameManager::GameManager() {
#ifdef DEBUG
	cout << "GameManager::construtor" << endl;
#endif
	
	string nome;
	char filePath[29] = IMAGEM_SPACETILE;	
	
	if (!SDLBase::inicializaSDL())
		cout << "Erro ao inciar SDL." << endl;
	camera.x = 0;
	camera.y= 0;
	cameraSpeed.x=0;
	cameraSpeed.y=0;
	backGround = new Sprite(IMAGEM_BACK_GROUND);
	planetSprite = new Sprite(IMAGEM_PLANETA);
	Sprite* auxTile = new Sprite(IMAGEM_SPACETILE);
	tilemap = new TileMap(16, 16, TILE_SIZE);
	tileset = new TileSet(auxTile->getWidth(), auxTile->getHeight());
	
	quit = false;
	
	for (int i = 1; i <= N_TEXTURES; i++) {
		filePath[23] = '0' + i % 10;
		filePath[22] = '0' + i / 10;
		tileset->addTile(filePath);

	}
	
	tilemap->setTileSet(tileset);
	buildMap();
}

GameManager::~GameManager() {
	if (backGround != NULL) {
		delete (backGround);
	}
	if (planetSprite != NULL) {
		delete (planetSprite);
	}
	if (tileset != NULL) {
		delete (tileset);
	}
	if (tilemap != NULL) {
		delete (tilemap);
	}
}
/*
 * run(): roda o loop principal do jogo
 */

void GameManager::run() {
#ifdef DEBUG
	cout << "GameManager::run" << endl;
#endif
	while (!quit) {
		/* Captura de Input */
		processEvents();
		/*Atualiza camera*/
		camera.x += cameraSpeed.x;
		camera.y += cameraSpeed.y;
		/* Atualização dos objetos */
		checkPlanet();
		/* Todos os comandos de renderização */
		backGround->render(0, 0);
		tilemap->render(camera.x, camera.y);
		for (std::vector<Planet*>::iterator it = planetArray.begin();
				it != planetArray.end(); ++it) {
			Planet* planet = *it;
			planet->render(camera.x, camera.y);
		}
		/* Atualizar a tela */
		SDLBase::atualizaTela();

	}
}
/*
 * addPlanet(): adiciona novos planetas ao array, com
 * posição e hitpoints aletórios.
 */

void GameManager::addPlanet() {
#ifdef DEBUG
	cout << "GameManager::addPlanet" << endl;
#endif
	Planet* novoPlanet;
	float hitPoints, x, y;
	hitPoints = (rand() % 19) + 1;
	x = (rand() % 800) + 1;
	y = (rand() % 600) + 1;
	x = x + camera.x;
	y = y + camera.y;
	novoPlanet = new Planet(planetSprite, hitPoints, x, y);

	planetArray.push_back(novoPlanet);

}

/*
 * checkPlanet(): Checa se deve retirar do array os
 * planetas com hitpoins menores que 0.
 */
void GameManager::checkPlanet() {
#ifdef DEBUG
	cout << "GameManager::checkPlanet" << endl;
#endif
	for (std::vector<Planet*>::iterator it = planetArray.end() - 1;
			it != planetArray.begin() - 1; --it) {
		Planet* planet = *it;
		if (planet->hitPoints < 0) {
			it = planetArray.erase(it);
		}
	}
}
/*
 * processEvents(): verificas os eventos de saida,
 * apertar teclas e adicionar planetas;
 * cliacar do mouse, que pode provovar baixa aleatoria
 * de hitpoints.
 */

void GameManager::processEvents() {
#ifdef DEBUG
	cout << "GameManager::processEvents" << endl;
#endif

	InputManager::getInstance().Update();
	if (InputManager::getInstance().keyDown[SDLK_ESCAPE]) {
				// se a tecla ESC foi pressionada, sair do programa
				quit = true;
	}
	// Determina as variáveis de velocidade da câmera
	// de acordo com as teclas pressionadas
	else if (InputManager::getInstance().isKeyPressed(SDLK_UP))
		cameraSpeed.y -= SCROLL;
	else if (InputManager::getInstance().isKeyPressed(SDLK_DOWN))
		cameraSpeed.y += SCROLL;
	else if (InputManager::getInstance().isKeyPressed(SDLK_LEFT))
		cameraSpeed.x -= SCROLL;
	else if (InputManager::getInstance().isKeyPressed(SDLK_RIGHT))
		cameraSpeed.x += SCROLL;
	else if (InputManager::getInstance().isKeyPressed(SDLK_SPACE)) {
		addPlanet();
	}

}



//	// procura um evento
//	SDL_Event event;
//	while (SDL_PollEvent(&event) && !quit) // inicializar um atributo quit do tipo bool com o valor false
//	{
//		// um evento foi achado
//		if (event.type == SDL_QUIT)
//			quit = true;
//		else if (event.type == SDL_MOUSEBUTTONDOWN) {
//			// obtém o estado do mouse
//			int mouseX, mouseY;
//			SDL_GetMouseState(&mouseX, &mouseY);
//
//			// percorre o array de planetas de forma invertida
//			// até achar o planeta que o usuário clicou.
//			// percorremos de forma invertida porque os últimos
//			// planetas são desenhados no topo, e estes serão
//			// atingidos primeiro
//			for (std::vector<Planet*>::iterator it = planetArray.end() - 1;
//					it != planetArray.begin() - 1; --it) {
//				Planet *planet = *it;
//
//				if (mouseX + camera.x >= planet->position.x
//						&& mouseX + camera.x
//								< planet->position.x
//										+ planet->sprite->getClip().w
//						&& mouseY + camera.y >= planet->position.y
//						&& mouseY + camera.y
//								< planet->position.y
//										+ planet->sprite->getClip().h) {
//					// acerta o planeta, dando dano aleatório entre 10 e 19
//
//					planet->hitPoints -= rand() % 10 + 10;
//
//					// acertamos apenas um planeta
//					// portanto saímos do break
//					break;
//				}
//			}
//		} else if (event.type == SDL_KEYDOWN) {
//			if (event.key.keysym.sym == SDLK_ESCAPE) {
//				// se a tecla ESC foi pressionada, sair do programa
//				quit = true;
//			}
//			// Determina as variÃ¡veis de velocidade da cÃ¢mera
//			// de acordo com as teclas pressionadas
//			else if (event.key.keysym.sym == SDLK_UP)
//				cameraSpeed.y -= SCROLL;
//			else if (event.key.keysym.sym == SDLK_DOWN)
//				cameraSpeed.y += SCROLL;
//			else if (event.key.keysym.sym == SDLK_LEFT)
//				cameraSpeed.x -= SCROLL;
//			else if (event.key.keysym.sym == SDLK_RIGHT)
//				cameraSpeed.x += SCROLL;
//			else if (event.key.keysym.sym == SDLK_SPACE) {
//				addPlanet();
//			}
//		} else if (event.type == SDL_KEYUP) {
//			// uma tecla foi solta
//
//			// diminui as variÃ¡veis de velocidade da cÃ¢mera
//			// para que elas voltam a ser zero caso uma tecla
//			// tenha sido solta
//			if (event.key.keysym.sym == SDLK_UP)
//				cameraSpeed.y += SCROLL;
//			else if (event.key.keysym.sym == SDLK_DOWN)
//				cameraSpeed.y -= SCROLL;
//			else if (event.key.keysym.sym == SDLK_LEFT)
//				cameraSpeed.x += SCROLL;
//			else if (event.key.keysym.sym == SDLK_RIGHT)
//				cameraSpeed.x -= SCROLL;
//		}
//	}
//	// fim do loop de eventos


void GameManager::buildMap() {
	tilemap->at(0, 0) = 0;
	tilemap->at(1, 0) = 1;
	tilemap->at(2, 0) = 1;
	tilemap->at(3, 0) = 1;
	tilemap->at(4, 0) = 1;
	tilemap->at(5, 0) = 1;
	tilemap->at(6, 0) = 1;
	tilemap->at(7, 0) = 1;
	tilemap->at(8, 0) = 1;
	tilemap->at(9, 0) = 1;
	tilemap->at(10, 0) = 1;
	tilemap->at(11, 0) = 1;
	tilemap->at(12, 0) = 5;
	tilemap->at(13, 0) = -1;
	tilemap->at(14, 0) = -1;
	tilemap->at(15, 0) = -1;
	tilemap->at(0, 1) = 6;
	tilemap->at(1, 1) = 10;
	tilemap->at(2, 1) = 10;
	tilemap->at(3, 1) = 10;
	tilemap->at(4, 1) = 10;
	tilemap->at(5, 1) = 10;
	tilemap->at(6, 1) = 10;
	tilemap->at(7, 1) = 10;
	tilemap->at(8, 1) = 10;
	tilemap->at(9, 1) = 10;
	tilemap->at(10, 1) = 10;
	tilemap->at(11, 1) = 10;
	tilemap->at(12, 1) = 11;
	tilemap->at(13, 1) = -1;
	tilemap->at(14, 1) = -1;
	tilemap->at(15, 1) = -1;
	tilemap->at(0, 2) = 12;
	tilemap->at(1, 2) = 7;
	tilemap->at(2, 2) = 8;
	tilemap->at(3, 2) = 8;
	tilemap->at(4, 2) = 8;
	tilemap->at(5, 2) = 8;
	tilemap->at(6, 2) = 8;
	tilemap->at(7, 2) = 8;
	tilemap->at(8, 2) = 9;
	tilemap->at(9, 2) = 10;
	tilemap->at(10, 2) = 10;
	tilemap->at(11, 2) = 10;
	tilemap->at(12, 2) = 17;
	tilemap->at(13, 2) = -1;
	tilemap->at(14, 2) = -1;
	tilemap->at(15, 2) = -1;
	tilemap->at(0, 3) = 6;
	tilemap->at(1, 3) = 13;
	tilemap->at(2, 3) = 14;
	tilemap->at(3, 3) = 14;
	tilemap->at(4, 3) = 14;
	tilemap->at(5, 3) = 14;
	tilemap->at(6, 3) = 14;
	tilemap->at(7, 3) = 14;
	tilemap->at(8, 3) = 15;
	tilemap->at(9, 3) = 10;
	tilemap->at(10, 3) = 10;
	tilemap->at(11, 3) = 10;
	tilemap->at(12, 3) = 11;
	tilemap->at(13, 3) = -1;
	tilemap->at(14, 3) = -1;
	tilemap->at(15, 3) = -1;
	tilemap->at(0, 4) = 12;
	tilemap->at(1, 4) = 13;
	tilemap->at(2, 4) = 14;
	tilemap->at(3, 4) = 14;
	tilemap->at(4, 4) = 14;
	tilemap->at(5, 4) = 14;
	tilemap->at(6, 4) = 14;
	tilemap->at(7, 4) = 14;
	tilemap->at(8, 4) = 15;
	tilemap->at(9, 4) = 7;
	tilemap->at(10, 4) = 25;
	tilemap->at(11, 4) = 28;
	tilemap->at(12, 4) = 29;
	tilemap->at(13, 4) = -1;
	tilemap->at(14, 4) = -1;
	tilemap->at(15, 4) = -1;
	tilemap->at(0, 5) = 6;
	tilemap->at(1, 5) = 13;
	tilemap->at(2, 5) = 14;
	tilemap->at(3, 5) = 14;
	tilemap->at(4, 5) = 14;
	tilemap->at(5, 5) = 14;
	tilemap->at(6, 5) = 14;
	tilemap->at(7, 5) = 14;
	tilemap->at(8, 5) = 15;
	tilemap->at(9, 5) = 19;
	tilemap->at(10, 5) = 3;
	tilemap->at(11, 5) = 4;
	tilemap->at(12, 5) = 5;
	tilemap->at(13, 5) = -1;
	tilemap->at(14, 5) = -1;
	tilemap->at(15, 5) = -1;
	tilemap->at(0, 6) = 6;
	tilemap->at(1, 6) = 13;
	tilemap->at(2, 6) = 14;
	tilemap->at(3, 6) = 14;
	tilemap->at(4, 6) = 14;
	tilemap->at(5, 6) = 14;
	tilemap->at(6, 6) = 14;
	tilemap->at(7, 6) = 14;
	tilemap->at(8, 6) = 15;
	tilemap->at(9, 6) = 10;
	tilemap->at(10, 6) = 10;
	tilemap->at(11, 6) = 10;
	tilemap->at(12, 6) = 11;
	tilemap->at(13, 6) = -1;
	tilemap->at(14, 6) = -1;
	tilemap->at(15, 6) = -1;
	tilemap->at(0, 7) = 12;
	tilemap->at(1, 7) = 13;
	tilemap->at(2, 7) = 14;
	tilemap->at(3, 7) = 14;
	tilemap->at(4, 7) = 14;
	tilemap->at(5, 7) = 14;
	tilemap->at(6, 7) = 14;
	tilemap->at(7, 7) = 14;
	tilemap->at(8, 7) = 15;
	tilemap->at(9, 7) = 10;
	tilemap->at(10, 7) = 10;
	tilemap->at(11, 7) = 10;
	tilemap->at(12, 7) = 17;
	tilemap->at(13, 7) = -1;
	tilemap->at(14, 7) = -1;
	tilemap->at(15, 7) = -1;
	tilemap->at(0, 8) = 6;
	tilemap->at(1, 8) = 19;
	tilemap->at(2, 8) = 20;
	tilemap->at(3, 8) = 20;
	tilemap->at(4, 8) = 20;
	tilemap->at(5, 8) = 20;
	tilemap->at(6, 8) = 20;
	tilemap->at(7, 8) = 20;
	tilemap->at(8, 8) = 21;
	tilemap->at(9, 8) = 10;
	tilemap->at(10, 8) = 10;
	tilemap->at(11, 8) = 10;
	tilemap->at(12, 8) = 11;
	tilemap->at(13, 8) = -1;
	tilemap->at(14, 8) = -1;
	tilemap->at(15, 8) = -1;
	tilemap->at(0, 9) = 24;
	tilemap->at(1, 9) = 25;
	tilemap->at(2, 9) = 25;
	tilemap->at(3, 9) = 25;
	tilemap->at(4, 9) = 25;
	tilemap->at(5, 9) = 25;
	tilemap->at(6, 9) = 25;
	tilemap->at(7, 9) = 25;
	tilemap->at(8, 9) = 25;
	tilemap->at(9, 9) = 26;
	tilemap->at(10, 9) = 26;
	tilemap->at(11, 9) = 26;
	tilemap->at(12, 9) = 29;
	tilemap->at(13, 9) = -1;
	tilemap->at(14, 9) = -1;
	tilemap->at(15, 9) = -1;
	tilemap->at(0, 10) = -1;
	tilemap->at(1, 10) = -1;
	tilemap->at(2, 10) = -1;
	tilemap->at(3, 10) = -1;
	tilemap->at(4, 10) = -1;
	tilemap->at(5, 10) = -1;
	tilemap->at(6, 10) = -1;
	tilemap->at(7, 10) = -1;
	tilemap->at(8, 10) = -1;
	tilemap->at(9, 10) = -1;
	tilemap->at(10, 10) = -1;
	tilemap->at(11, 10) = -1;
	tilemap->at(12, 10) = -1;
	tilemap->at(13, 10) = -1;
	tilemap->at(14, 10) = -1;
	tilemap->at(15, 10) = -1;
	tilemap->at(0, 11) = 0;
	tilemap->at(1, 11) = 1;
	tilemap->at(2, 11) = 1;
	tilemap->at(3, 11) = 5;
	tilemap->at(4, 11) = -1;
	tilemap->at(5, 11) = 0;
	tilemap->at(6, 11) = 2;
	tilemap->at(7, 11) = 3;
	tilemap->at(8, 11) = 4;
	tilemap->at(9, 11) = 5;
	tilemap->at(10, 11) = -1;
	tilemap->at(11, 11) = -1;
	tilemap->at(12, 11) = -1;
	tilemap->at(13, 11) = -1;
	tilemap->at(14, 11) = -1;
	tilemap->at(15, 11) = -1;
	tilemap->at(0, 12) = 6;
	tilemap->at(1, 12) = 7;
	tilemap->at(2, 12) = 28;
	tilemap->at(3, 12) = 29;
	tilemap->at(4, 12) = -1;
	tilemap->at(5, 12) = 12;
	tilemap->at(6, 12) = 10;
	tilemap->at(7, 12) = 10;
	tilemap->at(8, 12) = 10;
	tilemap->at(9, 12) = 17;
	tilemap->at(10, 12) = -1;
	tilemap->at(11, 12) = -1;
	tilemap->at(12, 12) = -1;
	tilemap->at(13, 12) = 0;
	tilemap->at(14, 12) = 5;
	tilemap->at(15, 12) = -1;
	tilemap->at(0, 13) = 18;
	tilemap->at(1, 13) = 17;
	tilemap->at(2, 13) = -1;
	tilemap->at(3, 13) = -1;
	tilemap->at(4, 13) = -1;
	tilemap->at(5, 13) = 6;
	tilemap->at(6, 13) = 10;
	tilemap->at(7, 13) = 10;
	tilemap->at(8, 13) = 10;
	tilemap->at(9, 13) = 11;
	tilemap->at(10, 13) = -1;
	tilemap->at(11, 13) = -1;
	tilemap->at(12, 13) = -1;
	tilemap->at(13, 13) = 24;
	tilemap->at(14, 13) = 29;
	tilemap->at(15, 13) = -1;
	tilemap->at(0, 14) = 24;
	tilemap->at(1, 14) = 29;
	tilemap->at(2, 14) = -1;
	tilemap->at(3, 14) = -1;
	tilemap->at(4, 14) = -1;
	tilemap->at(5, 14) = 24;
	tilemap->at(6, 14) = 25;
	tilemap->at(7, 14) = 27;
	tilemap->at(8, 14) = 28;
	tilemap->at(9, 14) = 29;
	tilemap->at(10, 14) = -1;
	tilemap->at(11, 14) = -1;
	tilemap->at(12, 14) = -1;
	tilemap->at(13, 14) = -1;
	tilemap->at(14, 14) = -1;
	tilemap->at(15, 14) = -1;
	// A linha 15 tem apenas -1, nao é necessário preenche-la, pois
	// o mapa é inicializado com -1
}

