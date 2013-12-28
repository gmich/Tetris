#include "menu.h"


Menu::Menu(){
	buffer=create_bitmap(SCREEN_W,SCREEN_H);
	clear_to_color(buffer,makecol(255,0,255));

	click = load_sample("content/click.wav");
	clickV=150;
	sfxDelay=16;
}


void Menu::clickSFX(){

	sfxDelay=Min(16,sfxDelay+1);
	if (sfxDelay>15){
		if (key[KEY_UP] || key[KEY_DOWN]){
			play_sample(click,clickV,124,1200,false);
			sfxDelay=0;
		}
	}
}

MainMenu::MainMenu(){
	button[0]= new Button(190,340,110,30,"Play");
	button[1]= new Button(190,400,110,30,"New Game");
	button[2]= new Button(190,460,110,30,"Options");
	button[3]= new Button(190,520,110,30,"About");
	button[4]= new Button(190,580,110,30,"Quit");
	selection = new Selection(5);
	label = new Label(195,250,100,25,"Main Menu");
	Menu();
	state=6;
}

MainMenu::~MainMenu(){
	for (int i=0;i<5;i++)
		delete button[i];
	delete selection;

}

void MainMenu::navigation(){


	clear_to_color(buffer,makecol(255,0,255));
	
	selection->handleButtonSelection();
	
	label->draw(buffer);

	for (int i=0;i<5;i++)
		button[i]->drawButton(buffer,false);

	switch (selection->getSelection()){
		case 0:
			button[0]->drawButton(buffer,true);
			break;
		case 1:
			button[1]->drawButton(buffer,true);
			break;
		case 2:
			button[2]->drawButton(buffer,true);
			break;
		case 3:
			button[3]->drawButton(buffer,true);
			break;
		case 4:
			button[4]->drawButton(buffer,true);
			break;
	}


	if (key[KEY_ENTER])
			setState();


}

void MainMenu::setState(){
	state=selection->getSelection();

	while (key[KEY_ENTER]){
		button[state]->drawPressed(buffer);
		draw_sprite(screen,buffer,0,0);
	}

}


Options::Options(){
	button[0] = new Button(190,340,110,30,"Show HelpGrid");
	bar[0] = new Bar(190,400,110,20,"SFX Volume");
	bar[1]= new Bar(190,450,110,20,"Master Volume");
	button[1]= new Button(190,510,110,30,"Music");
	button[2]= new Button(190,560,110,30,"Back");
	label = new Label(195,250,100,25,"Options");
	gridLabel = new Label(310,345,50,25,"On");
	musicLabel = new Label(310,515,50,25,"On");
	selection = new Selection(5);
	sfx = new VolumeHandler(110,110);
	master = new VolumeHandler(110,80);
	grid=true;
	music=true;
	Menu();
	state=5;
}


Options::~Options(){
	for (int i=0;i<3;i++)
		delete button[i];
	for (int i=0;i<2;i++)
		delete bar[i];
	delete selection;
	delete sfx;
	delete master;
	delete gridLabel;
	delete musicLabel;
}

int Options::getMidiVolume(){
	return master->getVolume();
}

int Options::getSFXVolume(){
	return sfx->getVolume();
}


void Options::navigation(){
	
	clear_to_color(buffer,makecol(255,0,255));
	selection->handleButtonSelection();
	label->draw(buffer);
	musicLabel->draw(buffer);
	gridLabel->draw(buffer);

	for (int i=0;i<3;i++)
		button[i]->drawButton(buffer,false);

	bar[0]->drawBar(buffer,sfx->getVolume(),false);
	bar[1]->drawBar(buffer,master->getVolume(),false);

	switch (selection->getSelection()){
		case 0:
			button[0]->drawButton(buffer,true);
			break;
		case 1:
			sfx->handleVolume();
			bar[0]->drawBar(buffer,sfx->getVolume(),true);
			break;
		case 2:
			master->handleVolume();
			bar[1]->drawBar(buffer,master->getVolume(),true);
			break;
		case 3:
			button[1]->drawButton(buffer,true);
			break;
		case 4:
			button[2]->drawButton(buffer,true);
			break;
	}

		if (key[KEY_ENTER])
			setState();

}

bool Options::getGridStatus(){
	return grid;
}

void Options::setState(){



	switch (selection->getSelection()){
		case 0:
			if (grid){
				gridLabel->setNewString("Off");
				grid=false;
			}
			else if (!grid){
				gridLabel->setNewString("On");
				grid=true;
			}
			state=0;
		break;
		case 3:
			if (music){
				musicLabel->setNewString("Off");
				music=false;
				midi_pause();
			}
			else if (!music){
				musicLabel->setNewString("On");
				music=true;
				midi_resume();
			}
			state=1;
			break;
		case 4:
			state=2;
			break;
		default:
			state=selection->getSelection();
			break;
	}


	if (selection->getSelection()!=1 && selection->getSelection()!=2){
		while (key[KEY_ENTER]  ){
			  button[state]->drawPressed(buffer);
			  draw_sprite(screen,buffer,0,0);
		}
	}

	if (selection->getSelection()==4){
		state=4;
	}
	if (selection->getSelection()==3)
		state=3;

}

NewGame::NewGame(){
	button[0]= new Button(190,340,110,30,"Practice");
	button[1]= new Button(190,400,110,30,"Challenge");
	button[2]= new Button(190,460,110,30,"Master");
	button[3]= new Button(190,520,110,30,"Back");
	label = new Label(195,250,100,25,"New Game");
	selection = new Selection(4);
	Menu();
	state=4;
}

NewGame::~NewGame(){
	delete button[0];
	delete button[1];
	delete button[2];
	delete button[3];
	delete selection;
}


void NewGame::navigation(){

	selection->handleButtonSelection();
	clear_to_color(buffer,makecol(255,0,255));
	label->draw(buffer);
	
	for (int i=0;i<4;i++)
		button[i]->drawButton(buffer,false);


	switch (selection->getSelection()){
		case 0:
			button[0]->drawButton(buffer,true);
			break;
		case 1:
			button[1]->drawButton(buffer,true);
			break;
		case 2:
			button[2]->drawButton(buffer,true);
			break;
		case 3:
			button[3]->drawButton(buffer,true);
			break;
	}


			if (key[KEY_ENTER])
			setState();
}

void NewGame::setState(){
	state=selection->getSelection();

	while (key[KEY_ENTER]){
		button[state]->drawPressed(buffer);
		draw_sprite(screen,buffer,0,0);
	}

}

About::About(){
	aboutBuf=create_bitmap(SCREEN_W,800);
	clear_to_color(aboutBuf,makecol(255,0,255));
	
		textprintf_centre_ex(aboutBuf,font,125,0,makecol(41, 86, 178),-1,"** Controls **");
		textprintf_ex(aboutBuf,font,10,40,makecol(255,255,255),-1,"<ARROW-UP> - Rotate Clockwise");
		textprintf_ex(aboutBuf,font,10,70,makecol(255,255,255),-1,"<ARROW-DOWN> - Increase Fall Rate");
		textprintf_ex(aboutBuf,font,10,100,makecol(255,255,255),-1,"<CTRL> - Rotate Clockwise");
		textprintf_ex(aboutBuf,font,10,130,makecol(255,255,255),-1,"<ARROW-LEFT> - Move Left");
		textprintf_ex(aboutBuf,font,10,160,makecol(255,255,255),-1,"<ARROW-RIGHT> - Move Right");
		textprintf_ex(aboutBuf,font,10,190,makecol(255,255,255),-1,"<X> -  Accelerate");
		textprintf_ex(aboutBuf,font,10,220,makecol(255,255,255),-1,"<SPACE> - Lock Target");
		textprintf_ex(aboutBuf,font,10,250,makecol(255,255,255),-1,"<SHIFT> - Swap Figure");
		textprintf_ex(aboutBuf,font,10,280,makecol(255,255,255),-1,"<ESCAPE> - Main Menu");

		textprintf_centre_ex(aboutBuf,font,125,330,makecol(41, 86, 178),-1,"** Game Modes **");
		textprintf_ex(aboutBuf,font,20,370,makecol(101, 156, 239),-1,"<Practise Mode> ");
		textprintf_ex(aboutBuf,font,10,400,makecol(255,255,255),-1,"Free Play");
		textprintf_ex(aboutBuf,font,20,430,makecol(101, 156, 239),-1,"<Challenge Mode>");
		textprintf_ex(aboutBuf,font,10,470,makecol(255,255,255),-1,"Increasing Blocks and Fall Rate");
		textprintf_ex(aboutBuf,font,20,510,makecol(101, 156, 239),-1,"<Master Mode>");
		textprintf_ex(aboutBuf,font,10,540,makecol(255,255,255),-1,"Accelerated Gameplay");

		textprintf_centre_ex(aboutBuf,font,125,590,makecol(41, 86, 178),-1,"** Credits **");
		textprintf_ex(aboutBuf,font,10,630,makecol(101, 156, 239),-1,"Programming By:");
		textprintf_ex(aboutBuf,font,20,660,makecol(255,255,255),-1,"George Michaelides");
		textprintf_ex(aboutBuf,font,10,700,makecol(101, 156, 239),-1,"Special Thanks To:");
		textprintf_ex(aboutBuf,font,20,740,makecol(255,255,255),-1,"zander ");

	upVisible=false;
	downVisible=true;
	downOffSet=550;
	currPos=0;
	state=0;

	button[0]= new Button(420,300,30,30,"^");
	button[1]= new Button(420,600,30,30,"v");
	button[2]= new Button(190,650,110,30,"Back");
	label = new Label(195,250,100,25,"About");	
	Menu();
}

About::~About(){
	destroy_bitmap(aboutBuf);
	for (int i=0;i<3;i++)
		delete button[i];
}

void About::navigation(){

	state=0;
	
	adjustBuffer();	

	label->draw(buffer);

	if (upVisible)
		button[0]->drawButton(buffer,false);
	if (downVisible)
		button[1]->drawButton(buffer,false);
	
	button[2]->drawButton(buffer,true);

	if (key[KEY_UP]){
		if (upVisible)
			button[0]->drawPressed(buffer);
		currPos=Max(0,currPos-2);
	}
	else if (key[KEY_DOWN]){
		if (downVisible)
			button[1]->drawPressed(buffer);
		currPos=Min(downOffSet,currPos+2);
	}

	//up and down arrow visibility
	if (currPos==0){
		upVisible=false;
		downVisible=true;
	}
	if (currPos>0 && currPos<downOffSet){
		upVisible=true;
		downVisible=true;
	}
	if (currPos==downOffSet){
		downVisible=false;
		upVisible=true;
	}

	setState();
}

void About::clickSFX(){
	if (key[KEY_ENTER])
		play_sample(click,clickV,124,2000,false);
}

void About::setState(){
	if (key[KEY_ENTER])
		button[2]->drawPressed(screen);
	while (key[KEY_ENTER]){
		state=1;
	}
}

void About::adjustBuffer(){
	clear_to_color(buffer,makecol(255,0,255));

	blit(aboutBuf,buffer,0,currPos,120,300,400,330);
}


HandleMenu::HandleMenu(){

	reset();
	gameMode=0;
	helpGrid=true;
	banner=create_bitmap(SCREEN_W,6*15+5);
	clear_to_color(banner,makecol(255,0,255));

	buffer = create_bitmap(SCREEN_W,SCREEN_H);
	clear_to_color(buffer,makecol(0,0,0));
}

HandleMenu::~HandleMenu(){
	destroy_bitmap(buffer);
	destroy_bitmap(banner);
}

void HandleMenu::reset(){
	mainState=5; //main menu states
	newgameState=4;
	optionsState=5;
	aboutState=0;
	exitStatus=false;
	startGame=false;
	resetgame=false;
	menu=&mainmenu;
}

int HandleMenu::getGameMode(){

	return gameMode;
}

bool HandleMenu::getExit(){
	return exitStatus;
}

bool HandleMenu::timeToPlay(){
	return startGame;
}

void HandleMenu::backCheck(){

	if (key[KEY_ESC]){
		menu->resetState();
		mainState=5;
		optionsState=5;
		aboutState=1;
		newgameState=4;
		menu=&mainmenu;
	}
}

void HandleMenu::navigation(){
	backCheck();
	menu->resetState();
	menu->navigation();
	menu->clickSFX();

	switch (mainState){
	case 0:
		//continue playing
		startGame=true;
		break;
	case 1:
		//new game	
		menu=&newgame;
		newgameState=menu->getState();

		break;
	case 2:
		//options
		menu=&options;
		optionsState=menu->getState();
		break;
	case 3:
		menu=&about;
		aboutState=menu->getState();
		break;
	case 4:
		//exit
		exitStatus=true;
		break;
	case 5:
		menu=&mainmenu;
		mainState=menu->getState();
		break;
	default:
		mainState=5;
		break;
	}

	
	switch(newgameState){
	case 0:
		gameMode=0;
		resetgame=true;
		startGame=true;
		menu->resetState();
		break;
	case 1:
		gameMode=1;
		resetgame=true;
		startGame=true;
		menu->resetState();
		break;
	case 2:
		gameMode=2;
		resetgame=true;
		startGame=true;
		menu->resetState();
		break;
	case 3:
		mainState=5;
		newgameState=4;
		menu->resetState();
		break;
	case 4:
		//idle
		break;
	}

	switch(optionsState){
	case 0:
		helpGrid=options.getGridStatus();
		break;
	case 1:  
		//sfx volume
		break;
	case 2:
		//midi volume
		break;
	case 3:
		//stop music
		break;
	case 4:
		mainState=5;
		optionsState=5;
		break;
	case 5:
		//idle;
		break;
	}

	switch(aboutState){
	case 0:
		//idle
		break;
	case 1:  
		mainState=5;
		aboutState=0;
		break;
	}

	//set menu volume
	menu->setClickV(options.getSFXVolume());
	updateScreen(menu->getBuffer());
	//check if the player wants to change screen with the escape key

}

bool HandleMenu::newGame(){
	return resetgame;
}

void HandleMenu::setBanner(BITMAP* buffer){

	draw_sprite(banner,buffer,0,0);
}

void HandleMenu::updateScreen(BITMAP* menuBuffer){
	clear_to_color(buffer,makecol(0,0,0));
	draw_sprite(buffer,menuBuffer,0,0);
	draw_sprite(buffer,banner,0,40);
	draw_sprite(screen,buffer,0,0);
}