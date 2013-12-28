#ifndef SOUNDHANDLER_H_INCLUDED
#define SOUNDHANDLER_H_INCLUDED
#include <allegro.h>

class SoundHandler{
private:
		SAMPLE* line;
		SAMPLE* rotate;
		SAMPLE* idle;
		int volume;
		int pan;
		int pitch;
public:
	SoundHandler();
	~SoundHandler();
	void lineSFX();
	void rotationSFX();
	void idleSFX();
	void setVolume(int volume);

};



#endif