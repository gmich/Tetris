#include "draw.h"


GameD::GameD(){
	
	buffer = create_bitmap(SCREEN_W,SCREEN_H);
	clear_to_color(buffer,makecol(0,0,0));
	bufferGame = create_bitmap(blockWidth*blockSize+1,blockHeight*blockSize+1); 
	clear_to_color(bufferGame,makecol(0,0,0)); 
	nextFigure=create_bitmap(15*blockSize+1,5*blockSize+1);
	clear_to_color(nextFigure,makecol(255,0,255));
	holdFigure=create_bitmap(15*blockSize+1,5*blockSize+1);
	clear_to_color(holdFigure,makecol(255,0,255));
	textBuff=create_bitmap(SCREEN_W,SCREEN_H);
	clear_to_color(textBuff,makecol(255,0,255)); 
	score=create_bitmap(100,260);
}

GameD::~GameD(){
	destroy_bitmap(buffer);
	destroy_bitmap(bufferGame);
	destroy_bitmap(nextFigure);
	destroy_bitmap(score);
	destroy_bitmap(textBuff);
}

void GameD::drawGrid(){
	
	//rectfill(buffer,0,0,blockWidth*blockSize+10,6,makecol(0,0,255));
	rectfill(buffer,0,0,SCREEN_W,SCREEN_H,makecol(0,0,100));
	for (int i=0;i<SCREEN_H;i+=20)
		hline(buffer,0,i,SCREEN_W,makecol(0,0,180));
	//background color
	rectfill(buffer,blockSize*blockWidth+12,0,SCREEN_W,SCREEN_H,makecol(11,11,11));
}
void GameD::getHold(BITMAP* buffer1){
	draw_sprite(holdFigure,buffer1,0,0);
}

void GameD::drawText(int gamemode,bool secondChance){
	clear_to_color(textBuff,makecol(255,0,255)); 
		if (gamemode==0)
		textprintf_centre_ex(textBuff,font,410,10,makecol(243, 213, 189),-1,"Practice");
	else if (gamemode==1)
		textprintf_centre_ex(textBuff,font,410,10,makecol(243, 213, 189),-1,"Challenge");
	else if (gamemode==2)
		textprintf_centre_ex(textBuff,font,410,10,makecol(243, 213, 189),-1,"Master");
	//	textprintf_centre_ex(textBuff,font,410,230,makecol(255,255,255),-1,"<X> Abort Figure");
		//if (secondChance)
			//textprintf_centre_ex(textBuff,font,410,190,makecol(101,156,239),-1,"Available");
		if (!secondChance)
			textprintf_ex(textBuff,font,340,210,makecol(255,0,0),-1,"UNAVAILABLE");

	textprintf_ex(textBuff,font,SCREEN_W-50,95,makecol(255,255,255),-1,"Next");
	textprintf_ex(textBuff,font,SCREEN_W-50,210,makecol(255,255,255),-1,"Swap");
	textprintf_centre_ex(textBuff,font,410,650,makecol(255,255,255),-1,"<ESCAPE> Menu");
}

void GameD::updateScreen(){
	
	drawGrid(); 
	draw_sprite(buffer,bufferGame,5,0);
    rectfill(buffer,0,blockSize*2,blockWidth*blockSize+10,blockSize*2+2,makecol(255,255,255)); //game over line

	rectfill(buffer,325-2,40-2,345+90+2,60+92,makecol(0, 0, 100));
	rectfill(buffer,325-2,160-2,345+90+2,180+90+2,makecol(0,0,100));
	blit(nextFigure,buffer,6*blockWidth+10,0,335,50,100,100);  //draw next figure onto the buffer	
	blit(holdFigure,buffer,6*blockWidth+10,0,335,170,100,100);
	for(int i=0;i<4;i+=2)
		rect(buffer,325-i,160-i,345+90+i,180+90+i,makecol(255,255,255));
	for(int i=0;i<4;i+=2)
		rect(buffer,325-i,40-i,345+90+i,60+90+i,makecol(255,255,255)); // draw rectangles around figure


	draw_sprite(buffer,score,360,300); //draw score to buffer

	for (int i=0;i<4;i+=2)
		rect(buffer,360+i,300+i,360+score->w-i,300+score->h-i,makecol(255,255,255)); //draw rectangles around the scoreboard
	
	draw_sprite(buffer,textBuff,0,0);
	draw_sprite(screen,buffer,0,0); //draw buffer onto the screen

	clear_to_color(bufferGame,makecol(0,0,0)); 
	clear_to_color(buffer,makecol(0,0,0));
}

BITMAP* GameD::getBuffer(){
	drawGrid(); 
	draw_sprite(buffer,bufferGame,5,0);
    rectfill(buffer,0,blockSize*2,blockWidth*blockSize+10,blockSize*2+2,makecol(255,255,255)); //game over line
	
	rectfill(buffer,325-2,40-2,345+90+2,60+92,makecol(0, 0, 100));
	rectfill(buffer,325-2,160-2,345+90+2,180+90+2,makecol(0,0,100));
	blit(nextFigure,buffer,6*blockWidth+10,0,335,50,100,100);  //draw next figure onto the buffer		
	blit(holdFigure,buffer,6*blockWidth+10,0,335,170,100,100);
	for(int i=0;i<4;i+=2)
		rect(buffer,325-i,160-i,345+90+i,180+90+i,makecol(255,255,255));

	for(int i=0;i<4;i+=2)
		rect(buffer,325-i,40-i,345+90+i,60+90+i,makecol(255,255,255)); // draw rectangles around figure
	draw_sprite(buffer,score,360,300); //draw score to buffer

	for (int i=0;i<4;i+=2)
		rect(buffer,360+i,300+i,360+score->w-i,300+score->h-i,makecol(255,255,255)); //draw rectangles around the scoreboard
	draw_sprite(buffer,textBuff,0,0);	
	return buffer;

}
void GameD::setBlit(BITMAP* buffer1){

	draw_sprite(nextFigure,buffer1,0,0);

}

void GameD::setScoreBuffer(BITMAP* buffer){

	draw_sprite(score,buffer,0,0);

}