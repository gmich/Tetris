#ifndef TETRISBOARD_H_INCLUDED
#define TETRISBOARD_H_INCLUDED

#include <cstdlib>
#include <allegro.h>
#include "block.h"
#include "figure.h"
#include "defines.h"
#include "animateline.h"
#include "soundhandler.h"
#include <list>
#include "score.h"

using std::list;


// TetrisBoard class is responsible for the stack of figures on screen  
//it's also responsible for collision and drawing each block
class TetrisBoard {
private:
	bool map[blockHeight][blockWidth]; //used to check for a complete line
	int challengeModeLines;
	bool targetLocked; //true if the target is locked, player may not move the figure 
	list<Block> idleBlocks; //list the stack of blocks
	BITMAP* buffer; //for the idleblocks + moving figure
	BITMAP* bufferN; //next figure
	BITMAP* bufferH; //hold figure
	BITMAP* transBlock;
	Figure* figure;
	Figure* nextFigure;
	Figure* holdFigure;
	AnimateLine* Line;
	SoundHandler* sfx;
	Score* score;
	double timePassed; //rising blocks in challenge mode
	int gameMode;
	int secondChanceCounter;
	int lowerLines;
	bool secondChance;
	bool incrementBlocks;
	int iCounter;
	bool idleCounter;
public:
	TetrisBoard();
	~TetrisBoard();
	void resetEverything();
	void startIdleCounter();
	//sliding figure onto the idle blocks stack
	bool getIdleCounter();
	void setMovingFigure(Figure* f);
	void checkSecondChance();
	void setNextFigure();
	void setHoldFigure();
	void moveFigureY(int gameMode);
	void moveFigureX(bool pos);
	void startClock();
	void clockIsTicking();
	void resetClock();
	void handleClock();
	void incrementClock();
	void moveBlocksAbove();
	void increaseFallRate();
	void aSecondChance();
	void destroyLowerLines();
	void setBackground();
	void rotateFigure(bool clockwise);
	//adds each block of the figure class into the idleblock list	
	void AddFigureToIdle();
	//set lines for destruction
	void setLines();
	void setVolume(int volume){sfx->setVolume(volume);};
	void destroyLine(int line);
	void newGame();
	void handleYCollision();
	void targetIsLocked() {targetLocked=true;};
	//checks if the blocks have reached the upper line
	bool overFlow(); 
	//dots that let the player know where the figure is heading, on/off option included
	void showHelpGrid();
	bool collideWhileRotating();
	bool getSecondChance(){return secondChance;};
	bool blocksAreFalling(){return Line->blocksAreFalling();};
	bool collideWhileMovingX(bool pos);
	bool collideWhileMovingY(Figure* f);
	//true after a line destruction and points increase, to be passed at the animateline class
	bool isPointAnimating();
	// if a line is  complete (all the blocks are idle) the line gets destroyed
	void checkLinesFromBellow(); 
	 //helpful function to choose color
	int getColor(int color);
	//BITMAPs are passed to the draw game class in main()
	BITMAP* getIdleBuffer();
	BITMAP* getNextFigure();
	BITMAP* getFallingBlocksBuffer();
	BITMAP* getMovingBuffer(bool showGrid);
	BITMAP* getScoreBuffer();
	BITMAP* getPointBuffer();
	BITMAP* getHoldFigure(){ return bufferH;};
	void setTransparentBlock(int color);
	// a factory that returns random figures
	Figure* spawner(); 
	// moving figure gets its value from nextfigure
	Figure* getFigure(Figure* f);
};



#endif