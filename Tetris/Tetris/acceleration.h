#ifndef ACCELERATION_H_INCLUDED
#define ACCELERATION_H_INCLUDED
#include <allegro.h>
#include "defines.h"

class AccelerationHandler{
private:
	int counterR,counterL,counterD,counterD2,Lcounter,Rcounter;
	bool rightIsTapped;
	bool leftIsTapped;
	bool downIsTapped;
	bool acceleratingLeft;
	bool acceleratingRight;
	bool rotate;
	bool acceleratingDown;
	int acceleration,accelerationL,accelerationR;
	bool lockOn;
	bool leftIsReleased,rightIsReleased;
	int left,right;
public:
	AccelerationHandler();
	void HandleLeft();
	void incrementLeft();
	void leftIsNotPressed();
	int massAccelerationL();
	int massAccelerationR();
	void HandleRight();
	void HandleDown();
	void resetDown();
	void resetLeft();
	void resetRight();
	void resetLCounter();
	void rotatingNotAllowed();
	bool allowRotation();
	void resetRCounter();
	void incrementRight();
	void instantAcceleration();
	int getAcceleration();
	int getAccelerationL();
	int gameMode(int gamemode);
	int getAccelerationR();
	bool handleMultipleTappingL();
	bool handleMultipleTappingR();
	void multipleTapping();
	bool getLockOn();
	void Handler();
};



#endif