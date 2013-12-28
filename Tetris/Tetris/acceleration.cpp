#include "acceleration.h"

AccelerationHandler::AccelerationHandler(){
	acceleration=0;
	left=right=0;
	rotate=true;
	resetLeft();
	resetRight();
	resetDown();
	resetLCounter();
	resetRCounter();
}

void AccelerationHandler::resetLeft(){
	leftIsTapped=false;
	counterL=11;
	acceleratingLeft=false;
	accelerationL=0;
}

void AccelerationHandler::resetDown(){
	downIsTapped=false;
	counterD=12;
	counterD2=0;
	acceleratingDown=false;
	lockOn=false;
}

int AccelerationHandler::gameMode(int gamemode){

	//master mode default acceleration
	if (gamemode==2)
		return 0;
	else
		return 0;
}

void AccelerationHandler::resetRight(){
	counterR=11;
	rightIsTapped=false;
	acceleratingRight=false;
	accelerationR=0;
}


void AccelerationHandler::HandleLeft(){

	
	if (!acceleratingLeft){
		if (key[KEY_LEFT]){
			counterL=0;
			leftIsTapped=true;
		}
	}

	if (!key[KEY_LEFT]){
		acceleratingLeft=true;
		counterL=Min(counterL+1,11);
		if (counterL==11){
			leftIsTapped=false;
			acceleratingLeft=false;
		}
	}

	if (acceleratingLeft && key[KEY_LEFT])
		accelerationL=2;
	else{
		accelerationL=0;
	}
}

void AccelerationHandler::HandleDown(){

	
	if (!acceleratingDown){
		if (key[KEY_DOWN]){
			counterD=0;
			downIsTapped=true;
		}
	}

	if (!key[KEY_DOWN]){
		acceleratingDown=true;
		counterD=Min(counterD+1,12);
		if (counterD==12){
			downIsTapped=false;
			acceleratingDown=false;
		}
	}

	if (acceleratingDown && key[KEY_DOWN]){
		lockOn=true;
	}
	else {
		lockOn=false;
	
	}

	if (lockOn)
		counterD2++;

	if (counterD2>1)
		resetDown();

}
void AccelerationHandler::rotatingNotAllowed(){
	rotate=false;
}

bool AccelerationHandler::allowRotation(){
	return ((key[KEY_UP] || key[KEY_LCONTROL]) && rotate);

}

void AccelerationHandler::HandleRight(){


	
	if (!acceleratingRight){
		if (key[KEY_RIGHT]){
			counterR=0;
			rightIsTapped=true;
		}
	}

	if (!key[KEY_RIGHT]){
		acceleratingRight=true;
		counterR=Min(counterR+1,11);
		if (counterR==11){
			rightIsTapped=false;
			acceleratingRight=false;
		}
	}

	if (acceleratingRight && key[KEY_RIGHT])
		accelerationR=2;
	else{
		accelerationR=0;
	}
}

void AccelerationHandler::instantAcceleration(){

	if (key[KEY_X]){
		acceleration=3;
	}
	else
		acceleration=0;

}

void AccelerationHandler::Handler(){
	HandleLeft();
	HandleRight();
	HandleDown();
	instantAcceleration();
	multipleTapping();

	if (!key[KEY_LEFT])
		left=0;
	if (!key[KEY_RIGHT])
		right=0;

	if (!key[KEY_UP] && !key[KEY_LCONTROL])
		rotate=true;

}

int AccelerationHandler::getAccelerationR(){
	return accelerationR;
}

void AccelerationHandler::incrementLeft(){
	left=Min(left+1,20);
}

void AccelerationHandler::incrementRight(){
	right=Min(right+1,20);
}



int AccelerationHandler::massAccelerationL(){
	if (left==2)
		return 3;
	if (left>=3)
		return 7;

		return 0;
}

int AccelerationHandler::massAccelerationR(){
	if (right==2)
		return 3;

	if (right>=3)
		return 7;

		return 0;
}

bool AccelerationHandler::getLockOn(){
	return lockOn;
}

int AccelerationHandler::getAcceleration(){
	return acceleration;
}

int AccelerationHandler::getAccelerationL(){
	return accelerationL;
}

void AccelerationHandler::resetLCounter(){
	Lcounter=0;
	leftIsReleased=false;
}

void AccelerationHandler::resetRCounter(){
	Rcounter=0;
	rightIsReleased=false;
}
void AccelerationHandler::multipleTapping(){
	Lcounter=Min(Lcounter+1,20);
	Rcounter=Min(Rcounter+1,20);
	if (!key[KEY_LEFT] && Lcounter<11)
		leftIsReleased=true;
	
	if (Lcounter>11)
		leftIsReleased=false;

	if (!key[KEY_RIGHT] && Lcounter<11)
		rightIsReleased=true;
	
	if (Rcounter>11)
		rightIsReleased=false;
}

bool AccelerationHandler::handleMultipleTappingL(){

	if (Lcounter<11 && leftIsReleased)
		return true;
	else
		return false;
}

bool AccelerationHandler::handleMultipleTappingR(){

	if (Rcounter<11 && rightIsReleased)
		return true;
	else
		return false;
}