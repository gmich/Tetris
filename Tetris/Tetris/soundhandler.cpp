#include <allegro.h>
#include "soundhandler.h"

SoundHandler::SoundHandler(){
	line=load_sample("content/line.wav");
	rotate=load_sample("content/rotate.wav");
	idle=load_sample("content/idle.wav");
	volume=150;
	pan=120;
	pitch=1100;
}

SoundHandler::~SoundHandler(){
	destroy_sample(line);
	destroy_sample(rotate);
	destroy_sample(idle);

}

void SoundHandler::setVolume(int volume){
	this->volume = volume;
}

void SoundHandler::lineSFX(){
	
   play_sample(line,volume,pan,2200,false);
}


void SoundHandler::rotationSFX(){
	
   play_sample(rotate,volume,pan,pitch,false);
}

void SoundHandler::idleSFX(){
	
   play_sample(idle,volume,pan,pitch,false);
}