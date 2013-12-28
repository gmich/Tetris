#ifndef STARTUP_H_INCLUDED
#define STARTUP_H_INCLUDED
#define block 15
#include <allegro.h>
#include "defines.h"

class StartUp{
private:
	BITMAP* buffer;
	int wait;
	int counter;
	int speed;
	bool abort;
	bool flag; //variable needed for text animation
	bool done;
public:
	StartUp();
	~StartUp();
	void updateScreen();
	void Abort();
	void drawT();
	void drawE();
	void drawT2();
	void drawR();
	void drawI();
	void drawS();
	void drawNames(); 
	void drawText(char ch,int x,int y);
	void animateScreen();  //animate screen at the end
	void drawRectangle(int x,int y);
	void drawCornice();
	void setSpeed(); //set speed for animateScreen
	bool isDone();
	//Animations after the tetris lineup
	void drawText();
	void setCounter();
	void swapFlag();
	//Handler
	void animateTitleScreen();
	BITMAP* getBanner(){ return buffer;};
};



#endif