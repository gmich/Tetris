#include "animateline.h"


AnimateLine::AnimateLine(){

	tempBuffer=create_bitmap(blockWidth*blockSize+1,blockHeight*blockSize+1);
	fallingBuffer=create_bitmap(blockWidth*blockSize+1,blockHeight*blockSize+1);
	clear_to_color(fallingBuffer,makecol(255,0,255));
	clear_to_color(tempBuffer,makecol(255,0,255));
	stopAnimation();
	stopFallingAnimation();
}


void AnimateLine::abortAll(){

	stopAnimation();
	stopFallingAnimation();

}

void AnimateLine::startAnimation(){

	status=true;

}

void AnimateLine::stopAnimation(){
	vectorY.clear();
	frame=0;
	status=false;
}

void AnimateLine::pauseAnimation(){

	status=false;

}

void AnimateLine::setLine(int line){
	blockCounter=blockCounter+15;
	vectorY.push_back(line);

}

bool AnimateLine::isAnimating(){

	return status;

}


void AnimateLine::animate(BITMAP* buffer){
	falling=true;
	if (frame<blockWidth){
		frame++;
	list<int>::iterator p = vectorY.begin();
		while(p != vectorY.end()){  
			rectfill(tempBuffer,0,*p*blockSize, frame*blockSize,*p*blockSize+blockSize, makecol(0,0,0));
			//hline(tempBuffer,(frame)*blockSize-30,*p*blockSize+blockSize/2,frame*blockSize-3,makecol(200,200,200));
			isAFallingPiece(frame*blockSize,*p*blockSize,false);
			p++;
			
		}		
		animateFallingPieces();
	}
	else stopAnimation();

	draw_sprite(buffer,tempBuffer,0,0);
	
}

void AnimateLine::isAFallingPiece(int x, int y,bool active){
	Vector2D* vector;

	vector = new Vector2D(x,y,active);

	vector2D.push_back(*vector);

	delete vector;
}


void AnimateLine::animateFallingPieces(){

	clear_to_color(fallingBuffer,makecol(255,0,255));
		list<Vector2D>::iterator p = vector2D.begin();
		while(p != vector2D.end()){  
			rect(fallingBuffer,p->getX()-blockSize,p->getY(),p->getX(),p->getY()+blockSize, makecol(120,120,120));

			if (p->isActive())
				for (int i=0;i<7;i++)
					p->setY();
			else
				p->setY();

			if (p->getY()>SCREEN_H+blockSize){
				p=vector2D.erase(p);
				eraseCounter++;
			}
			p++;
		}
		if (eraseCounter==blockCounter)
			stopFallingAnimation();
}

void AnimateLine::blocksAreFalling(int blocks){
	blockCounter+=blocks;
	falling=true;
}

void AnimateLine::stopFallingAnimation(){
	falling=false;
	eraseCounter=0;
	blockCounter=0;
	vector2D.clear();
}
void AnimateLine::setBuffer(BITMAP* buffer1){
	
	clear_to_color(tempBuffer,makecol(255,0,255));
	draw_sprite(tempBuffer,buffer1,0,0);
	
}