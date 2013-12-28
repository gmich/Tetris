#include "startup.h"


StartUp::StartUp(){
	buffer=create_bitmap(SCREEN_W,6*block+5);
	clear_to_color(buffer,makecol(255,0,255));
	wait=50;
	abort=false;
	counter=255;
	flag=false;
	done=false;
	speed=240;
}


StartUp::~StartUp(){
	destroy_bitmap(buffer);

}

void StartUp::updateScreen(){

	draw_sprite(screen,buffer,0,240);

	rest(wait);
}

bool StartUp::isDone(){

	return done;

}

void StartUp::drawRectangle(int x,int y){

	rect(buffer,x,y,x+block,y+block,makecol(0,0,255));
	rectfill(buffer,x+1,y+1,x+block-1,y+block-1,makecol(255,255,255));
	
	updateScreen();

}

void StartUp::drawT(){
	
	for (int i=1;i<6;i++)
		drawRectangle(block*i,10);

	for (int i=0;i<4*block;i+=block)
		drawRectangle(block*3,25+i);

}

void StartUp::drawE(){
	
	for (int i=8*block;i<=10*block;i+=block)
		drawRectangle(i,10);

	for (int i=0;i<3*block;i+=block)
		drawRectangle(block*8,25+i);

	for (int i=8*block;i<=10*block;i+=block)
		drawRectangle(i,10+4*block);

	drawRectangle(9*block,2*block+10);

}

void StartUp::drawT2(){
	
	for (int i=1;i<6;i++)
		drawRectangle(12*block+block*i,10);

	for (int i=0;i<4*block;i+=block)
		drawRectangle(block*12+block*3,25+i);

}

void StartUp::drawR(){
	for (int i=0;i<=4*block;i+=block)
		drawRectangle(block*20,10+i);

	for (int i=21*block;i<=22*block;i+=block)
		drawRectangle(i,10);

	for (int i=21*block;i<=22*block;i+=block)
		drawRectangle(i,2*block+10);

	drawRectangle(22*block,block+10);
	drawRectangle(21*block+8,3*block+10);
	drawRectangle(21*block+17,4*block+10);

}


void StartUp::drawI(){
	
	for (int i=0;i<=4*block;i+=block)
		drawRectangle(block*25,10+i);

}


void StartUp::drawS(){

	drawRectangle(block*28,10);
	drawRectangle(block*29,10);
	drawRectangle(block*30,10);
	drawRectangle(block*28+5,10+block);
	drawRectangle(block*28+15,10+2*block);
	drawRectangle(block*28+25,10+3*block);
	drawRectangle(block*28+30,10+4*block);
	drawRectangle(block*29,10+4*block);
	drawRectangle(block*28,10+4*block);
}

void StartUp::drawCornice(){

	for (int i=1;i<9;i+=2){
		rect(buffer,i,i,buffer->w-i,buffer->h-i,makecol(0,0,255));
		updateScreen();
	}
}


void StartUp::Abort(){

	if (keypressed()){
		abort=true;
		wait=0;
	}

}

void StartUp::drawText(){
	BITMAP* textBuf;
	textBuf = create_bitmap(150,50);
	clear_to_color(textBuf,makecol(255,0,255));
	
	  while (!keypressed() && !abort){
		textprintf_ex(textBuf,font,5,5, makecol(counter,counter,counter), -1, "<Press Any Key>");
		draw_sprite(screen,textBuf,SCREEN_W/2-60, SCREEN_H/2+3*block);
		setCounter();
	}

	clear_to_color(textBuf,makecol(0,0,0));
	draw_sprite(screen,textBuf,SCREEN_W/2-60, SCREEN_H/2+5*block);
	destroy_bitmap(textBuf);
	animateScreen();
}


void StartUp::setCounter(){
	rest(5);
	if (flag){
		counter-=2;
		counter=Max(0,counter);
	}
	else if (!flag){
		counter+=2;
		counter=Min(counter,255);
	}

	if ((counter==0) || (counter==255))
		swapFlag();

}

void StartUp::swapFlag(){

	if (flag)
		flag=false;
	else if (!flag)
		flag=true;
}


void StartUp::animateScreen(){
	BITMAP* tempBuffer;

	tempBuffer=create_bitmap(SCREEN_W,SCREEN_H);

	while (!done){
		clear_to_color(tempBuffer,makecol(0,0,0));
		draw_sprite(tempBuffer,buffer,0,speed);
		draw_sprite(screen,tempBuffer,0,0);
		setSpeed();
		
	}
}

void StartUp::setSpeed(){

	speed-=1;

	if (speed< 40)
		done=true;

}

void StartUp::animateTitleScreen(){

	drawT();
	Abort();
	drawE();
	Abort();
	drawT2();
	Abort();
	drawR();
	Abort();
	drawI();
	Abort();
	drawS();
	Abort();
	drawCornice();
	Abort();
	drawNames();
	Abort();
	drawText();

}


void StartUp::drawNames(){
	char title[]="Programming by:";
	char name1[]="George Michaelides";


	for (int i=0;i<15;i++)
		drawText(title[i],i,0);
		Abort();

	for (int i=0;i<18;i++)
		drawText(name1[i],i,1);
		Abort();

}


void StartUp::drawText(char ch,int x,int y){
	textprintf_ex(screen,font,300+x*10,600+y*18,makecol(255,255,255),-1,"%c",ch);
	rest(wait);
}