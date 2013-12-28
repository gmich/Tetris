#include "score.h"

Score::Score(){

	buffer=create_bitmap(100,260);
	scoreboard=create_bitmap(SCREEN_W,SCREEN_H);
	clear_to_color(scoreboard,makecol(255,0,255));
	pointBuffer=create_bitmap(blockWidth*blockSize+1,blockHeight*blockSize+1);
	highScore=0;
	swapscreen=new SwapScreen;
	resetEverything();
	resetAnimation();

	ifstream hScore("content/highscore.txt");

    if (!hScore) {
        cout << "Could not find highscore.txt ";
    }
	else
       hScore>>highScore;
   
}

Score::~Score(){
	destroy_bitmap(buffer);
	destroy_bitmap(pointBuffer);
	destroy_bitmap(scoreboard);
	delete swapscreen;
}

void Score::resetColors(){

	red=green=blue=gray=yellow=brown=purple=cornflowerBlue=orange=0;
	lines=0; 
	currScore=0;
	clear_to_color(buffer,makecol(0,0,115));
	clear_to_color(pointBuffer,makecol(255,0,255));
}

void Score::resetEverything(){

	resetColors();
	currHScore=0;
	linesSum=0;
	animation=false;

}

void Score::addLine(){

	lines++;

}

void Score::scoreBoard(){
	clear_to_color(scoreboard,makecol(255,0,255));

	
	rectfill(scoreboard,130,SCREEN_H/2-150,320,SCREEN_H/2+30,makecol(101,156,239));
	textprintf_ex(scoreboard, font, 185, SCREEN_H/2-130, makecol(0, 51, 102), -1,
        "HighScore");
	textprintf_ex(scoreboard, font, 180, SCREEN_H/2-100, makecol(255, 204, 0), -1,
        "%d", highScore);

	textprintf_ex(scoreboard, font, 185, SCREEN_H/2-60, makecol(0, 51, 102), -1,
        "Score");
	textprintf_ex(scoreboard, font,180, SCREEN_H/2-30, makecol(255, 204, 0), -1,
        "%d",currHScore);

	for (int i=0;i<8;i+=2)
	rect(scoreboard,130+i,SCREEN_H/2-150+i,320-i,SCREEN_H/2+30-i,makecol(41, 86, 178));

	draw_sprite(screen,scoreboard,0,0);
	rest(600);
	clear_keybuf();
	swapscreen->waitForKey();

}

void Score::setColors(int color){

	animatePoints();

	switch (color){

	case 0:
		orange++;
		currScore+=orange*2;
		break;
	case 1:
		green++;
		currScore+=green*2;
		break;
	case 2:
		blue++;
		currScore+=blue*2;
		break;
	case 3:
		gray++;
		currScore+=gray*2;
		break;
	case 4:
		yellow++;
		currScore+=yellow*2;
		break;
	case 5:
		brown++;
		currScore+=brown*2;
		break;
	case 6:
		purple++;
		currScore+=purple*2;
		break;
	case 7:
		cornflowerBlue++;
		currScore+=cornflowerBlue*2;
	case 8:
		red++;
		currScore+=red*2;
	default:
		red++;	
		currScore+=red*2;
		break;
	
	}
	pointAnimation=currScore;
}

void Score::setHighScore(){

	currHScore+=currScore;
	linesSum+=lines;
	if (currHScore>highScore)
		highScore=currHScore;

	currScore=0;

	saveHighScore();
}
	
void Score::saveHighScore(){
	ofstream hScore;
	
	hScore.open("content/highscore.txt");
	if (hScore.is_open()) {
		hScore<<highScore;
		hScore.close();
	}
	else 
		cout<<"Error saving highScore";
	
}

BITMAP* Score::getScoreBuffer(){

	setHighScore();
	resetColors();

		 textprintf_centre_ex(buffer, font, (buffer->w)/2, 30, makecol(255,255,255), -1,
        "HighScore");
		textprintf_centre_ex(buffer, font, (buffer->w)/2, 50, makecol(255,255,255), -1,
        "%d", highScore);
		
		textprintf_centre_ex(buffer, font, (buffer->w)/2, 110, makecol(255,255,255), -1,
        "Score");
	    textprintf_centre_ex(buffer, font, (buffer->w)/2, 130, makecol(255,255,255), -1,
        "%d", currHScore);

		textprintf_centre_ex(buffer, font, (buffer->w)/2, 190, makecol(255,255,255), -1,
        "Lines");
	    textprintf_centre_ex(buffer, font, (buffer->w)/2, 210, makecol(255,255,255), -1,
        "%d", linesSum);

	return buffer;

}

void Score::animatePoints(){

	animation=true;

}


bool Score::isAnimating(){

	return animation;

}

void Score::setLine(int line){

	posCounter=line*blockSize;
	animation=true;

}

void Score::textout_stretch( BITMAP *bmp, int x , int y , double multiplier ,int color ){
	 BITMAP *temp;
	   
	temp = create_bitmap( text_length(font,"acbd"), text_height(font));
	clear_to_color( temp , makecol( 255 , 0 , 255 ) );
	textprintf_ex(temp,font,0,0,color,-1,"%d",pointAnimation);
	masked_stretch_blit( temp , pointBuffer , 0 , 0 , temp -> w , temp -> h , x , y , (int)(temp -> w * multiplier), (int)(temp -> h * multiplier)); 
	   
     destroy_bitmap( temp );	
}

BITMAP* Score::getPointBuffer(){
	
	clear_to_color(pointBuffer,makecol(255,0,255));

	if (fontCounter>0){
	
		//textprintf_centre_ex(pointBuffer, font, pointBuffer->w/2, posCounter, makecol(fontCounter,0,0), -1,  "+ %d");
		textout_stretch(pointBuffer,pointBuffer->w/2-yOffSet,posCounter,stretchCounter,makecol(fontCounter,0,0));
		fontCounter-=2;
		posCounter--;
		stretchCounter+=0.008;
		yOffSet=int(stretchCounter)*2;
	}
	else 
		resetAnimation();
	

	return pointBuffer;
}

      
void Score::resetAnimation(){
		stretchCounter=0.8;
		fontCounter=255;
		posCounter=0;
		yOffSet=0;
		pointAnimation=0;
		animation=false;
}


void Score::abort(){
	resetAnimation();
	resetColors();
}