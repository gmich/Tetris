#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED
#include "utilities.h"
#include "allegro.h"
#include <iostream>

//class prototype
class Menu{
protected:
	BITMAP* buffer;
	int state;
	Label* label;
	SAMPLE* click;
	int clickV;
	int sfxDelay;
public:
	Menu();
	virtual void navigation(){};
	virtual int getState(){return state;};
	virtual void setState(){};
	virtual void resetState(){};
	virtual void clickSFX();
	virtual void setClickV(int clickV){ this->clickV=clickV; };
	virtual BITMAP* getBuffer(){return buffer;};
};


class MainMenu : public Menu{
private:
	Button* button[5]; // play,newgame,options,about,quit
	Selection* selection;
public:
	MainMenu();
	~MainMenu();
	void navigation();
	void setState();
	void resetState() { state=5;}
};

class NewGame : public Menu{
private:
	Button* button[4]; 
	Selection* selection;
public:
	NewGame();
	~NewGame();
	void navigation();
	void setState();
	void resetState() { state=4;}
};



class Options : public Menu{
private:
	Button* button[3]; //classic/challenge mode, helpGrid, mute, back
	Bar* bar[2]; // soundfx , music
	Selection* selection;
	VolumeHandler* sfx;
	VolumeHandler* master;
	Label* gridLabel;
	Label* musicLabel;
	bool grid;
	bool music;
public:
	Options();
	~Options();
	void navigation();
	void setState();
	bool getGridStatus();
	void resetState() { state=5;}
	int getMidiVolume();
	int getSFXVolume();
};

class About : public Menu{
private:
	Button* button[3]; //up,down,back
	BITMAP* aboutBuf;
	bool upVisible; //if the up arrow is visible
	bool downVisible; //if the down arrow is visible
	int downOffSet; // maximum size of buffer
	int currPos; //current position
public:
	About();
	~About();
	void navigation();
	void setState();
	void adjustBuffer();
	void clickSFX();
};

class HandleMenu {
private:
	Menu* menu;
	BITMAP* buffer;
	BITMAP* banner;
	MainMenu mainmenu;
	Options options;
	NewGame  newgame;
	About about;
	bool exitStatus;
	bool startGame;
	bool helpGrid;
	bool resetgame;
	int gameMode; // 0 for classic , 1 for challenge
	int mainState;
	int newgameState;
	int optionsState;
	int aboutState;
public:
	HandleMenu();
	~HandleMenu();
	int getGameMode();
	void navigation();
	void reset();
	int getMidiVolume(){return options.getMidiVolume();};
	int getSFXVolume(){return options.getSFXVolume();};
	void backCheck();
	bool getExit();
	bool newGame();
	bool helpGridVisible(){return helpGrid;};
	bool timeToPlay();
	void setBanner(BITMAP* buffer);
	void updateScreen(BITMAP* menuBuffer);
};

#endif

