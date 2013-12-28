#include <allegro.h>
#include <iostream>
#include "tetrisboard.h"
#include "draw.h"
#include "startup.h"
#include "defines.h"
#include "utilities.h"
#include "acceleration.h"
#include "menu.h"

volatile int counter;
volatile int ticks;
volatile int framerate;
volatile int resting, rested;
volatile int midiLength;
volatile int pos;

//calculate framerate every second
void timer1(void)
{
    counter++;
    framerate = ticks;
    ticks=0;
    rested=resting;
}
END_OF_FUNCTION(timer1)


//do something while resting
void rest1(void)
{
    resting++;
}


static int timeSinceLastInputL=12;
static int timeSinceLastInputR=12;
static int timeSinceLastRotation=13;
static int timeSinceLastLock=20;
static int acceleration=0;
static int accelerationL=0;
static int accelerationR=0;

static AccelerationHandler accelerationhandler;


//HandleInput function is called in main() returns an integer according to the keypressed function
//A switch case is used in main() to determine the next action
int HandleInput(){	

	accelerationhandler.Handler();
	acceleration=accelerationhandler.getAcceleration();
	//accelerationL=accelerationhandler.getAccelerationL();
	//accelerationR=accelerationhandler.getAccelerationR();

	timeSinceLastInputL=Min(timeSinceLastInputL+1+accelerationL+acceleration+accelerationhandler.massAccelerationL(),12);
	timeSinceLastInputR=Min(timeSinceLastInputR+1+accelerationR+acceleration+accelerationhandler.massAccelerationR(),12);

	timeSinceLastRotation=Min(timeSinceLastRotation+1,13);
	timeSinceLastLock=Min(timeSinceLastLock+1,20);

	//	if (accelerationhandler.getLockOn()) //double downclick
	//	return 6;
	
	if (key[KEY_LEFT] && key[KEY_RIGHT])
		return 0;

	if (key[KEY_LEFT]){
		if (accelerationhandler.handleMultipleTappingL()){
			accelerationhandler.resetLCounter();
			return 1;
		}
		if (timeSinceLastInputL>=11){
			accelerationhandler.incrementLeft();
			accelerationhandler.resetLCounter();
			return 1;
		}
	}

	if (key[KEY_RIGHT]){
		if (accelerationhandler.handleMultipleTappingR()){
			accelerationhandler.resetRCounter();
			return 1;
		}
		if (timeSinceLastInputR>=11){
			accelerationhandler.incrementRight();
			accelerationhandler.resetRCounter();
			return 2;
		}
	}

    if (key[KEY_DOWN])
		return 3;

	if (key[KEY_UP] || key[KEY_LCONTROL]){
		if (accelerationhandler.allowRotation()){
			accelerationhandler.rotatingNotAllowed();
			return 4;
		}
	}
	if (key[KEY_SPACE]){
		if (timeSinceLastLock>=20)
			return 6;
	}

	if (key[KEY_LSHIFT] || key[KEY_RSHIFT])
		return 7;

	if (key[KEY_ESC])
		return 5;

		return 0;
}


int main(){


	//Allegro initialisation
	allegro_init();
	install_keyboard();
	install_timer();
	srand(time(NULL));
    LOCK_VARIABLE(counter);
    LOCK_VARIABLE(framerate);
    LOCK_VARIABLE(ticks);
    LOCK_VARIABLE(resting);
    LOCK_VARIABLE(rested);
    LOCK_FUNCTION(timer1);
    LOCK_FUNCTION(rest1);
    install_int(timer1, 1000);

	if (install_sound(DIGI_AUTODETECT, MIDI_AUTODETECT, NULL) != 0) {
      allegro_message("Error initializing sound system\n%s\n", allegro_error);
      return 1;
   }

	MIDI* tetrisTheme;

	//load the midi file
	tetrisTheme = load_midi("content/tetrisTheme.mid");
	if (!tetrisTheme) {
		allegro_message("Error loading Midi file");
		return 1;
	}
	
	//change color depth according to gfx card
	//set_color_depth(32);
	int depth;
	      if ((depth = desktop_color_depth()) != 0) {
	 set_color_depth(depth);
      }

	//intitialize alpha channel 
	 COLOR_MAP global_trans_table;
	 PALLETE mypallete;
     create_trans_table(&global_trans_table, mypallete, 128, 128, 128, NULL);
	 
      if (get_color_depth() == 8)
	 color_map = &global_trans_table;
      else
	 set_trans_blender(128, 128, 128, 85);

	
	//load gfx 
	int ret = set_gfx_mode(GFX_AUTODETECT_WINDOWED,500,705,0,0);
	
	if (ret) {
		allegro_message(allegro_error);
		return 1;
	}
	//End of Allegro initialisation


	enum GameStates{TitleScreen,Game,Menu};
	GameStates gamestate=TitleScreen;
	HandleMenu* menu;
	int keyPressed;
	int gameMode=0; //0 for classic mode, 1 for callenge mode
	TetrisBoard tetris;
	GameD game;
	StartUp* startup;
	SwapScreen* swapscreen;
	swapscreen = new SwapScreen;
	startup = new StartUp;
	menu = new HandleMenu;
	bool firstGame=true; // necessary to get the first targetbuffer for the first menu-game animation
	bool exitStatus=false;
	bool helpGrid=true;
	bool newGame=false;
	set_volume(80,80); //midi volume

	
	if (play_midi(tetrisTheme, 0) != 0) {
			allegro_message("Error playing Midi\n%s", allegro_error);
			return 1;
		}

	midiLength=get_midi_length(tetrisTheme);


//*****************************
//********GAME_LOOP************
	while(!exitStatus){
	
		//slow the game down
	    ticks++;    
        resting=0;
        rest_callback(10, rest1);

		voice_set_volume(10,10);
		pos = midi_time;
		if (pos>=midiLength)
			play_midi(tetrisTheme, 0);

		switch (gamestate){
		
			case TitleScreen:
				//show titleScreenHere
				startup->animateTitleScreen();
				menu->setBanner(startup->getBanner());
				delete startup;
								
				gamestate=Game;
				while(key[KEY_ENTER]);

				break;
				
			case Game:
				keyPressed=HandleInput();

				tetris.moveFigureY(gameMode);

				switch (keyPressed){	
				case 1:
					tetris.moveFigureX(true);
					timeSinceLastInputL=0+accelerationhandler.gameMode(gameMode);
					break;
				case 2:
					tetris.moveFigureX(false);
					timeSinceLastInputR=0+accelerationhandler.gameMode(gameMode);
					break;
				case 3:
					tetris.increaseFallRate();				
					break;
				case 4:
					tetris.rotateFigure(true);
					timeSinceLastRotation=0;
					break;
				case 5:
					gamestate=Menu;
					swapscreen->setSourceBuffer(screen);
					swapscreen->exchangeGame();
					break;
				case 6:
					tetris.targetIsLocked();
					timeSinceLastLock=0;
					break;
				case 7:
					tetris.aSecondChance();
					break;
				}
			
				game.setBuffer(tetris.getIdleBuffer());
				game.setBuffer(tetris.getMovingBuffer(helpGrid));
				if (tetris.blocksAreFalling())
				game.setBuffer(tetris.getFallingBlocksBuffer());
				if (tetris.isPointAnimating())
					game.setBuffer(tetris.getPointBuffer());
				game.setBlit(tetris.getNextFigure());
				game.getHold(tetris.getHoldFigure());
				game.setScoreBuffer(tetris.getScoreBuffer());
				game.drawText(gameMode,tetris.getSecondChance());
				if (newGame){
					swapscreen->setTargetBuffer(game.getBuffer());
					swapscreen->exchangeGame();
					swapscreen->waitForKey();
					newGame=false;
				}
				if (firstGame){
					gamestate=Menu;
					swapscreen->setSourceBuffer(game.getBuffer());
					firstGame=false;
				}
				if (gamestate==Game)
					game.updateScreen();
				break;
		
			case Menu:

				menu->navigation();
				exitStatus=menu->getExit();
				gameMode=menu->getGameMode();
				if (menu->timeToPlay()){
					if (menu->newGame()){
						tetris.newGame();
						newGame=true;
					}
					gamestate=Game;
					
					swapscreen->setSourceBuffer(screen);
				
					if (!menu->newGame()){
						swapscreen->exchangeGame();
						swapscreen->waitForKey();	
					}

					menu->reset();
				}
				helpGrid=menu->helpGridVisible();
				tetris.setVolume(menu->getSFXVolume()); 
				set_volume(menu->getMidiVolume(),menu->getMidiVolume()); //use midi_pause, midi_resume routines
				//if a player enters the menu with the escape button 
				//cant exit until the escape button is released
				while (key[KEY_ESC]);

				break;
		}
		
	}

	//******END_OF_GAME_LOOP************
	//********************************

	stop_midi();
	delete menu;
	delete swapscreen;
	destroy_midi(tetrisTheme);

	return 0;


}

 
END_OF_MAIN();


