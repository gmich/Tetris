#ifndef DRAW_H_INCLUDED
#define DRAW_H_INCLUDED
#include "defines.h"
#include <allegro.h>


//DrawGame class draws the main game onto the screen
class GameD {
private:
	BITMAP* buffer;
	BITMAP* bufferGame;
	BITMAP* nextFigure;
	BITMAP* holdFigure;
	BITMAP* score;
	BITMAP* textBuff;
public:
	GameD();
	~GameD();
	void setBuffer(BITMAP* buffer) { draw_sprite(bufferGame,buffer,0,0); };
	void getFallingBuffer(BITMAP* buffer);
	void getIdleBuffer(BITMAP* buffer);
	void setScoreBuffer(BITMAP* buffer);
	void setBlit(BITMAP* buffer1);
	void getHold(BITMAP* buffer1);
	void updateScreen();
	void drawText(int gamemode,bool secondChance);
    void drawGrid();
	void drawText();
	BITMAP* getBuffer();

};




#endif