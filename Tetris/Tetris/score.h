#ifndef SCORE_H_INCLUDED
#define SCORE_H_INCLUDED

#include <allegro.h>
#include <iostream>
#include <fstream>
#include "defines.h"
#include "utilities.h"
using namespace std;

class Score{
private:
		int currScore; //score for each line
		int highScore; //high score
		int currHScore; //current high score
		int lines;
		int linesSum; //number of lines
		bool animation;
		int red,green,blue,gray,yellow,brown,purple,cornflowerBlue,orange;
		BITMAP* buffer;
		BITMAP* pointBuffer;
		BITMAP*	scoreboard;
		SwapScreen* swapscreen;
		int fontCounter;
		int posCounter;
		int yOffSet;
		int pointAnimation;
		double stretchCounter;
public:
	Score();
	~Score();
	void resetColors();
	void resetEverything();
	void setColors(int color);
	void setHighScore();
	void saveHighScore();
	void addLine();
	void setLine(int line);
	void animatePoints();
	void setYOffSet();
	void abort(); //if its already animating and there is another point animation required
	bool isAnimating();
	void resetAnimation();
	void setStretchCounter();
	void textout_stretch( BITMAP *bmp,int x,int y,double multiplier,int color);
	int getCurrHScore(){return currHScore;};
	void scoreBoard();
	BITMAP* getScoreBuffer();
	BITMAP* getPointBuffer();
};



#endif