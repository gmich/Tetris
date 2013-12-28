#ifndef FIGURE_H_INCLUDED
#define FIGURE_H_INCLUDED
#include "block.h"
#include <iostream>
#include "defines.h"
#include <allegro.h>

//Figure class generates figures of blocks
//Figure class is the prototype class for each figure
//responsible for each block
class Figure{
protected:
	Block figure[4];
	int state; //rotation state
public:
	//sets state to 1 and a random color and all blocks to 0,0
	Figure(); 
	//describes each individual figure	
	virtual void initialize(){};
	virtual void rotation(int clockWise){};
	virtual Block getFigure(int i) { return figure[i]; } ;
	virtual void setFigure(Block block,int i){ figure[i]=block;};
	virtual int getState() { return state; };
	virtual void targetLocked(){  for (int i=0;i<4;i++)figure[i].targetLocked();}
	virtual void setX(int val,int pos){figure[pos].setX(val,true);};
	virtual void setColor(int color){ for (int i=0;i<4;i++)figure[i].setColor(color); };
	virtual void setCoordinates(int y){ for( int i=0;i<4;i++) figure[i].setY(-y);};
	virtual void moveFigureY(){for (int i=0;i<4;i++) figure[i].setY();};
	virtual void moveFigureX(bool pos){for (int i=0;i<4;i++) figure[i].setX(pos);};
	virtual void increaseFallRate(){for (int i=0;i<4;i++) figure[i].increaseFallRate();};
	virtual void decreaseFallRate(int gameMode,int score){for (int i=0;i<4;i++) figure[i].decreaseFallRate(gameMode,score);};
	virtual int getX(int pos){ return figure[pos].getX(); };
	virtual int getY(int pos){ return figure[pos].getY(); };
	virtual int getColor(int pos) { return figure[pos].getColor(); } ;
	virtual int getFallRate(int pos) { return figure[pos].getFallRate(); };
};


//Describe each figure here and then use an object factory in TetrisBoard class to spawn
class Figure1: public Figure{
public:
	Figure1():Figure(){};
	void rotation(int clockWise);
	virtual void initialize();

};

class Figure2: public Figure{
public:
	Figure2():Figure(){};
	void rotation(int clockWise);
	virtual void initialize();
};


class Figure3: public Figure{
public:
	Figure3():Figure(){};
	void rotation(int clockWise);
	virtual void initialize();
};

class Figure4: public Figure{
public:
	Figure4():Figure(){};
	void rotation(int clockWise);
	virtual void initialize();
};

class Figure5: public Figure{
public:
	Figure5():Figure(){};
	void rotation(int clockWise);
	virtual void initialize();
};

class Figure6: public Figure{
public:
	Figure6():Figure(){};
	void rotation(int clockWise);
	virtual void initialize();
};

class Figure7: public Figure{
public:
	Figure7():Figure(){};
	void rotation(int clockWise);
	virtual void initialize();
};

//TODO: add more figures here



#endif 