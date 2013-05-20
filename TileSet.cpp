/*
 * TileSet.cpp
 *
 *  Created on: May 11, 2013
 *      Author: LOUISE
 */
#include "TileSet.h"



//TileSet::TileSet(filePath string,int, int columns, int lines )
TileSet::TileSet(int tileWight, int tileHeight, string filePath ){
		this->tileHeight=tileHeight;
		this->tileWidth=tileWight;
		this->tileSet= NULL;
		this->userSingleFile=true;
		this->columns=0;
		this->lines=0;
		this->destRect=NULL;
		vTiles=NULL;

}

TileSet::TileSet(int tileWight, int tileHeight){
	this->tileHeight=tileHeight;
	this->tileWidth=tileWight;
	this->tileSet= 0;
	this->userSingleFile=false;
	this->columns=0;
	this->lines=0;
	this->destRect=NULL;
	vTiles=new std::vector<Sprite*>();
}

TileSet::~TileSet(){

 }

void TileSet::addTile(string filePath){
	if(!usingSingleFile()){
		vTiles->push_back(new Sprite(filePath));
	}else{
		cout<<"(TileSet::addTile)Erro:TileSet esta configurado para usar um unico Tile."<<endl;
	}
}

void TileSet::render(int index, float posX, float posY){
	if(usingSingleFile()){

	}else{

		vTiles->operator [](index)->Sprite::render(posX,posY);

	}

}

bool TileSet::usingSingleFile(){
	if(this->tileSet!=NULL){
		return true;
	}else{
		return false;
	}
}

int TileSet::getTileWidth(){
	return this->tileWidth;
}

int TileSet::getTileHeight(){
	return this->tileHeight;
}


