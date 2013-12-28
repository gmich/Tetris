#ifndef BLOCK_H_INCLUDED
#define BLOCK_H_INCLUDED
#include "defines.h"


//Block class describes each block
//movement is pixel based
class Block{
protected:
		int x,y;//Coordinates
		int fallRate;
		int color; //each number describes 1 color
		int lowerFallRate; 
public:
		Block();
		~Block();
		Block(int x,int y);
		int getX();
		int getY();
		int getFallRate();
		 //fallRate+2
		void increaseFallRate();
		 //fallRate is locked at 19 pixels per frame
		void targetLocked() {fallRate=19;};
		//fallRate-1
		void decreaseFallRate(int gameMode,int score);
		//changes according to fallRate
		void setY(); 
		//true for right , false for left
		void setX(bool axis);
		void setX(int x);
		void setX(int x,bool t);
		void setY(int y);
		void setColor(int color);
		int getColor();
};

#endif