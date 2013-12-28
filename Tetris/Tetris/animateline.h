#ifndef ANIMATELINES_H_INCLUDED
#define ANIMATELINES_H_INCLUDED
#include "defines.h"
#include <allegro.h>
#include <list>


using std::list;

class Vector2D{
private:
	int x,y;
	bool active;
public:
	Vector2D(){x=y=0; active=false;};
	Vector2D(int x,int y,bool active){this->x=x;this->y=y; this->active=active;};
	bool isActive(){return active;};
	int getX(){return x;};
	int getY(){return  y;};
	void setX(int x){this->x=x;};
	void setY(){y+=2;};
	void setY(int y){this->y=y;};
};

//AnimateLine animates the destruction of each block
class AnimateLine{
private:
	bool status;  //if there is animation
	bool falling;
	int frame; //current frame
	list<int> vectorY; //line coordinate
	list<Vector2D> vector2D;
	BITMAP* tempBuffer;
	BITMAP* fallingBuffer;
	int eraseCounter;
	int blockCounter;
public:
	AnimateLine();
	void startAnimation();
	void stopAnimation();
	bool isAnimating();
	void abortAll();
	void blocksAreFalling(int blocks);
	bool blocksAreFalling(){return falling;};
	void setBuffer(BITMAP* buffer1);
	void setLine(int line);
	void pauseAnimation();
	void animate(BITMAP* buffer);
	void stopFallingAnimation();
	void animateFallingPieces();
	void isAFallingPiece(int x, int y,bool active);
	BITMAP* getFallingBuffer(){return fallingBuffer;};
};


#endif