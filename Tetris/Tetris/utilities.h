#include <allegro.h>
#include "defines.h"
#ifndef UTILITIES_H_INCLUDED
#define UTILITIES_H_INCLUDED

class Button{
private:
	int x,y;
	int sizeX,sizeY;
	char text[50];
public:
	Button(int x,int y,int sizeX,int sizeY,char* string);
	void drawDefault(BITMAP* buffer);
	void drawSelected(BITMAP* buffer);
	void drawPressed(BITMAP* buffer);
	void drawTextDefault(BITMAP* buffer);
	void drawTextSelected(BITMAP* buffer);
	void drawButton(BITMAP* buffer,bool selection); //handler
};


class Bar{
private:
	int x,y;
	int sizeX,sizeY;
	char text[50];
public:
	Bar(int x,int y,int sizeX,int sizeY,char* string);
	void drawDefault(BITMAP* buffer,int volume);
	void drawSelected(BITMAP* buffer,int volume);
	void drawLever(BITMAP* buffer,int volume);
	void drawTextDefault(BITMAP* buffer);
	void drawTextSelected(BITMAP* buffer);
	void drawBar(BITMAP* buffer,int volume,bool selection); //handler
};



class Selection{
private:
	int maxSelection;
	int currSelection;
	int timeSinceLastInput;
public:
	Selection(int maxSelection);
	void next();
	void previous();
	void handleButtonSelection();
	int getSelection();
};

class Label{
private:
	int x,y;
	int sizeX,sizeY;
	char text[50];
public:
	Label(int x,int y,int sizeX,int sizeY,char* string);
	void draw(BITMAP* buffer);
	void setNewString(char* string);
};


//volume handler
class VolumeHandler{
private:
	int max;
	int volume;
public:
	VolumeHandler(int max,int volume);
	void increase();
	void decrease();
	int getVolume();
	void setVolume(int volume);
	void handleVolume();
};


class SwapScreen{
private:
	BITMAP* targetBuffer;
	BITMAP* sourceBuffer;
	BITMAP* buffer;
	int counter;
	bool flag;
public:
	SwapScreen();
	~SwapScreen();
	void setSourceBuffer(BITMAP* sBuffer);
	void setTargetBuffer(BITMAP* tBuffer);
	void exchangeGame();
	void setCounter();
	void waitForKey();
	void swapFlag();
};




#endif
