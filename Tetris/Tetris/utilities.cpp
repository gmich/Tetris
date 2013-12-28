#include "utilities.h"

Button::Button(int x,int y,int sizeX,int sizeY,char* string){
	this->x=x;
	this->y=y;
	this->sizeX=sizeX;
	this->sizeY=sizeY;
	strcpy(text,string);

}

void Button::drawDefault(BITMAP* buffer){

	for (int i=1;i<6;i++)
		rectfill(buffer,x+i,y+i,x+sizeX+i,y+sizeY+i,makecol(60,60,60)); //buttons gray shadow

	rectfill(buffer,x,y,x+sizeX,y+sizeY,makecol(255,255,255)); //button white fill

}

void Button::drawSelected(BITMAP* buffer){

	for (int i=1;i<6;i++)
		rectfill(buffer,x+i,y+i,x+sizeX+i,y+sizeY+i,makecol(153,217,234)); //buttons light blue shadow

	rectfill(buffer,x,y,x+sizeX,y+sizeY,makecol(0,0,255)); //button deep blue fill

}

void Button::drawPressed(BITMAP* buffer){

	rectfill(buffer,x-1,y-1,x+sizeX+6,y+sizeY+6,makecol(0,0,0)); //draw a black rectangle to cover the old button

	for (int i=5;i<6;i++)
		rectfill(buffer,x+i,y+i,x+sizeX+i,y+sizeY+i,makecol(153,217,234)); //buttons light blue shadow

	rectfill(buffer,x+4,y+4,x+sizeX+4,y+sizeY+4,makecol(0,0,255)); //button deep blue fill
	textprintf_centre_ex(buffer, font, x+(sizeX/2)+4, y+(sizeY/2)+4, makecol(255,255,255), -1, "%s",text);
}

void Button::drawTextDefault(BITMAP* buffer){

	 textprintf_centre_ex(buffer, font, x+(sizeX/2), y+(sizeY/2), makecol(0,0,0), -1, "%s",text);
}


void Button::drawTextSelected(BITMAP* buffer){

	 textprintf_centre_ex(buffer, font, x+(sizeX/2), y+(sizeY/2), makecol(255,255,255), -1, "%s",text);
}

void Button::drawButton(BITMAP* buffer,bool selection){

	if (selection){
		drawSelected(buffer);
		drawTextSelected(buffer);
	}
	else if (!selection){
		drawDefault(buffer);
		drawTextDefault(buffer);
	}

}


Bar::Bar(int x,int y,int sizeX,int sizeY,char* string){
	this->x=x;
	this->y=y;
	this->sizeX=sizeX;
	this->sizeY=sizeY;
	strcpy(text,string);

}


void Bar::drawDefault(BITMAP* buffer,int volume){

	rectfill(buffer,x-2,y-11,x+sizeX+2,y+sizeY+11,makecol(0,0,0));	//draw a black rectangle to cover the old one
	rect(buffer,x,y,x+sizeX,y+sizeY,makecol(255,255,255)); //bar white rectangle
	rectfill(buffer,x-1,y+1,x+volume,y+sizeY-1,makecol(153,217,234));//bar gray fill

	drawLever(buffer,volume);
}

void Bar::drawLever(BITMAP* buffer,int volume){
	 
	rect(buffer,x+volume-2,y-10,x+volume+2,y+sizeY+10,makecol(255,255,255));//lever rectangle
	rectfill(buffer,x+volume-1,y-9,x+volume+1,y+sizeY+9,makecol(200,200,200));//lever fill
}

void Bar::drawSelected(BITMAP* buffer,int volume){
	rectfill(buffer,x-2,y-11,x+sizeX+2,y+sizeY+11,makecol(0,0,0)); //draw a black rectangle to cover the old one
	rect(buffer,x,y,x+sizeX,y+sizeY,makecol(0,0,255)); //bar white rectangle
	rectfill(buffer,x-1,y+1,x+volume,y+sizeY-1,makecol(0,0,255));//bar gray fill

	drawLever(buffer,volume);

}

void Bar::drawTextDefault(BITMAP* buffer){

	textprintf_centre_ex(buffer, font, x-55, y+(sizeY/2), makecol(255,255,255), -1, "%s",text);
}


void Bar::drawTextSelected(BITMAP* buffer){

	textprintf_centre_ex(buffer, font, x-55, y+(sizeY/2), makecol(0,0,255), -1, "%s",text);
}

//class handler
void Bar::drawBar(BITMAP* buffer,int volume,bool selection){

	if (selection){
		drawSelected(buffer,volume);
		drawTextSelected(buffer);
	}
	else {
		drawDefault(buffer,volume);
		drawTextDefault(buffer);
	}
}



Selection::Selection(int maxSelection){
	currSelection=0;
	timeSinceLastInput=16;
	this->maxSelection=(maxSelection-1);
}

void Selection::next(){
	currSelection++;

	if (currSelection>maxSelection)
		currSelection=0;
}

void Selection::handleButtonSelection(){
	timeSinceLastInput=Min(timeSinceLastInput+1,16);
	
	if (key[KEY_UP])
		if (timeSinceLastInput>15){
			previous();
			timeSinceLastInput=0;
	}
	if (key[KEY_DOWN])
		if (timeSinceLastInput>15){
			next();
			timeSinceLastInput=0;
	}

}

void Selection::previous(){

	currSelection--;

	if (currSelection<0)
		currSelection=maxSelection;
}

int Selection::getSelection(){

	return currSelection;
}



VolumeHandler::VolumeHandler(int max,int volume){
	this->max=max;
	this->volume=volume;
}

void VolumeHandler::setVolume(int volume){
	this->volume = volume;
}

void VolumeHandler::increase(){
	volume++;
}

void VolumeHandler::decrease(){
	 volume--;
}

int VolumeHandler::getVolume(){
	return volume;
}

void VolumeHandler::handleVolume(){

	if (key[KEY_RIGHT])
		volume=Min(volume+1,max);

	if (key[KEY_LEFT])
		volume=Max(volume-1,0);

}



Label::Label(int x,int y,int sizeX,int sizeY,char* string){
	this->x=x;
	this->y=y;
	this->sizeX=sizeX;
	this->sizeY=sizeY;
	strcpy(text,string);

}


void Label::draw(BITMAP* buffer){

	for (int i=0;i<6;i+=2)
		rect(buffer,x+i,y+i,x+sizeX-i,y+sizeY-i,makecol(0,0,255-i*40)); //labels' frame

	rectfill(buffer,x+4,y+4,x+sizeX-4,y+sizeY-4,makecol(0,0,0)); //draw a black rectangle to erase old text 
	textprintf_centre_ex(buffer, font, x+(sizeX/2), y+(sizeY/3)+1, makecol(255,255,255), -1, "%s",text);

}

void Label::setNewString(char* string){

	strcpy(text,string);
}


SwapScreen::SwapScreen(){
	targetBuffer=create_bitmap(SCREEN_W,SCREEN_H);
	clear_to_color(targetBuffer,makecol(0,0,0));
	sourceBuffer=create_bitmap(SCREEN_W,SCREEN_H);
	buffer=create_bitmap(SCREEN_W*2,SCREEN_H);
	counter=255;
	flag=false;
}

SwapScreen::~SwapScreen(){
	destroy_bitmap(targetBuffer);
	destroy_bitmap(sourceBuffer);
	destroy_bitmap(buffer);
}


void SwapScreen::setSourceBuffer(BITMAP* sBuffer){
	draw_sprite(targetBuffer,sourceBuffer,0,0);
	draw_sprite(sourceBuffer,sBuffer,0,0);
}

void SwapScreen::setTargetBuffer(BITMAP* tBuffer){
	draw_sprite(targetBuffer,tBuffer,0,0);
}

void SwapScreen::exchangeGame(){
	blit(sourceBuffer,buffer,0,0,0,0,SCREEN_W,SCREEN_H);
	blit(targetBuffer,buffer,0,0,SCREEN_W,0,SCREEN_W,SCREEN_H);
	for (int i=0;i<=SCREEN_W;i+=1)
		blit(buffer,screen,i,0,0,0,SCREEN_W,SCREEN_H);
		//draw_sprite(screen,buffer,i,0);
}


void SwapScreen::waitForKey(){
	BITMAP* textBuf;
	textBuf = create_bitmap(150,50);
	clear_to_color(textBuf,makecol(255,0,255));
	counter=255;
	flag=false;

	rest(20);
	clear_keybuf();
	  while (!keypressed()){
		textprintf_ex(textBuf,font,5,5, makecol(counter,counter,counter), -1, "<Press Any Key>");
		draw_sprite(screen,textBuf,160, SCREEN_H/2);
		setCounter();
	}
	rest(20);
	  
	destroy_bitmap(textBuf);

}


void SwapScreen::setCounter(){
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

void SwapScreen::swapFlag(){

	if (flag)
		flag=false;
	else if (!flag)
		flag=true;
}


