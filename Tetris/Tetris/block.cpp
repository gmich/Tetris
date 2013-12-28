#include "block.h"
#include <iostream>



Block::Block(){
	x=y=0;
	fallRate=1;
	lowerFallRate=1;
	color=1;
}

Block::Block(int x,int y){
	this->x=x;
	this->y=y;
	fallRate=1;
	lowerFallRate=1;
	color=9;
}


Block::~Block(){
	//debugging
	//std::cout<<"a block is destroyed"<<std::endl;

};

int Block::getX(){

	return x;

}

int Block::getY(){
	
	return y;

}

int Block::getFallRate(){

	return fallRate;

}

void Block::increaseFallRate(){

	fallRate=Min(fallRate+2,15);

};

//adjust fallRate according to the score
void Block::decreaseFallRate(int gameMode,int score){

	//challenge
	if (gameMode==1){
		if (score>1000)
			lowerFallRate=2; 
		if (score>6000)
			lowerFallRate=3;
		if (score>15000)
			lowerFallRate=4;
		if (score>65000)
			lowerFallRate=5;
		if (score>80000)
			lowerFallRate=6;
	}
	else if (gameMode==0)
		lowerFallRate=1;
	else if (gameMode==2){ //master
		lowerFallRate=4;
		if (score>15000)
			lowerFallRate=5; 
		if (score>40000)
			lowerFallRate=6;
		if (score>80000)
			lowerFallRate=7;
	}

	fallRate=Max(fallRate-1,lowerFallRate);

};

void Block::setY(){

	y+=fallRate;

}


void Block::setX(bool axis){

	if (axis)
		x-=blockSize;
	else
		x+=blockSize;

}

void Block::setX(int x,bool t){
	this->x=x;
}
void Block::setX(int x){

	this->x+=x;

}

void Block::setY(int y){

	this->y+=y;

}


void Block::setColor(int color){

	this->color=color;

}


int Block::getColor(){

	return color;

}

