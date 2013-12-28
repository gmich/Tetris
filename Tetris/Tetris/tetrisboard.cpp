#include "tetrisboard.h"



TetrisBoard::TetrisBoard(){

	sfx = new SoundHandler;
	Line = new AnimateLine;
	score = new Score;

	timePassed=0;
	incrementBlocks=false;
	gameMode=0;
	buffer=create_bitmap(blockWidth*blockSize+1,blockHeight*blockSize+1);
	clear_to_color(buffer,makecol(255,0,255));

	transBlock=create_bitmap(19,19);
	clear_to_color(transBlock,makecol(255,0,255));
	//next figure buffer
	bufferN=create_bitmap(15*blockSize+1,5*blockSize+1);
	clear_to_color(bufferN,makecol(0,0,0));

	bufferH=create_bitmap(15*blockSize+1,5*blockSize+1);
	clear_to_color(bufferH,makecol(0,0,0));
	resetEverything();

	setNextFigure();
	setMovingFigure(nextFigure);
	setNextFigure();

}

TetrisBoard::~TetrisBoard(){

	delete Line;
	delete sfx;
	delete score;
	destroy_bitmap(buffer);
	destroy_bitmap(bufferN);
	destroy_bitmap(bufferH);
	destroy_bitmap(transBlock);
}

void TetrisBoard::resetEverything(){
	Block* block;
	block = new Block;
	targetLocked=false;
	//offscreen block to get the collision list loop going
	//if the list is empty , the collision loop does not start
	block->setY(blockHeight*blockSize+blockSize*100);
	block->setX(-blockHeight*10);
	idleBlocks.clear();
	//add a random block to start the loop
	idleBlocks.push_back(*block); 
	Line->abortAll();
	//all map blocks are false
	for (int i=0;i<blockHeight;i++)
		for (int j=0;j<blockWidth;j++)
			map[i][j]=false;

	challengeModeLines=0;
	timePassed=0;
	lowerLines=0;
	secondChanceCounter=601;
	idleCounter=false;
	incrementBlocks=false;
	iCounter=20;
	setHoldFigure();
	delete block;

}


//figure generator, nextFigure gets its value
Figure* TetrisBoard::spawner(){
	
	switch ((rand() % (maxFigure)) + 1){
	case 1:
		return new Figure1();
	case 2: 
		return new Figure2();
	case 3:
		return new Figure3();
	case 4:
		return new Figure4();
	case 5:
		return new Figure5();
	case 6:
		return new Figure6();
	case 7:
		return new Figure7();
	default:
		return new Figure2();
	}
}

//according to the nextFigure typeid, a new figure is sent to the moving figure
Figure* TetrisBoard::getFigure(Figure* f){

	if (typeid(*f)==typeid(Figure1))
		return new Figure1();
	if (typeid(*f)==typeid(Figure2))
		return new Figure2();
	if (typeid(*f)==typeid(Figure3))
		return new Figure3();
	if (typeid(*f)==typeid(Figure4))
		return new Figure4();
	if (typeid(*f)==typeid(Figure5))
		return new Figure5();
	if (typeid(*f)==typeid(Figure6))
		return new Figure6();
	if (typeid(*f)==typeid(Figure7))
		return new Figure7();

		return new Figure1();
}

void TetrisBoard::setNextFigure(){

	nextFigure=spawner();

	nextFigure->initialize();



	clear_to_color(bufferN,makecol(0, 0, 102));

	for (int i=0;i<4;i++){
			rect(bufferN,nextFigure->getX(i)+1,nextFigure->getY(i),
			nextFigure->getX(i)+blockSize,nextFigure->getY(i)+blockSize,makecol(255,255,255));
			rectfill(bufferN,nextFigure->getX(i)+2,nextFigure->getY(i)+1,
			nextFigure->getX(i)+blockSize-1,nextFigure->getY(i)+blockSize-1,getColor(nextFigure->getColor(i)));
	}
}

void TetrisBoard::setHoldFigure(){
	holdFigure=spawner();
	holdFigure->initialize();

	clear_to_color(bufferH,makecol(0, 0, 102));

	for (int i=0;i<4;i++){
			rect(bufferH,holdFigure->getX(i)+1,holdFigure->getY(i),
			holdFigure->getX(i)+blockSize,holdFigure->getY(i)+blockSize,makecol(255,255,255));
			rectfill(bufferH,holdFigure->getX(i)+2,holdFigure->getY(i)+1,
			holdFigure->getX(i)+blockSize-1,holdFigure->getY(i)+blockSize-1,getColor(holdFigure->getColor(i)));
	}

}

BITMAP* TetrisBoard::getNextFigure(){

	return bufferN;

}

void TetrisBoard::checkSecondChance(){

	secondChanceCounter=Min(secondChanceCounter+1,600);
	if(secondChanceCounter>500)
		secondChance=true;
	else secondChance=false;
}

void TetrisBoard::setMovingFigure(Figure* f){
	
	figure=getFigure(f);
	figure->initialize();
	figure->setColor(f->getColor(0));
	targetLocked=false;

	if (incrementBlocks){
		moveBlocksAbove();
		incrementBlocks=false;
		challengeModeLines++;
	}

}

void TetrisBoard::newGame(){
	resetEverything();
	score->resetEverything();
	setMovingFigure(nextFigure);
	setNextFigure();
}

void TetrisBoard::clockIsTicking(){
	timePassed=Min(timePassed+1,700);

	handleClock();
}

//challenge mode counter
void TetrisBoard::handleClock(){

	if (timePassed>450){
		incrementBlocks=true;
		timePassed=0;
	}
}

void TetrisBoard::resetClock(){
	timePassed=0;
}


void TetrisBoard::moveFigureY(int gameMode){
	
	checkSecondChance();
	this->gameMode=gameMode;

	if (getIdleCounter()){
		if (collideWhileMovingY(figure)){
			AddFigureToIdle();
			setMovingFigure(nextFigure);
			setNextFigure();
		}
	}

	if (overFlow()){
		score->scoreBoard();
		resetEverything();
		score->resetEverything();
	}

	if (gameMode==1)	
		clockIsTicking();
	else
		resetClock();

	if (targetLocked){	
		figure->targetLocked();
		while (!collideWhileMovingY(figure))
		figure->moveFigureY();
		 //if the figure collides , figure individual blocks are added to the idle list and new random blocks generated
		AddFigureToIdle();
		setMovingFigure(nextFigure);
		setNextFigure();
	}
	else{
		figure->decreaseFallRate(gameMode,score->getCurrHScore());
		handleYCollision();
	}

}

void TetrisBoard::handleYCollision(){
		if (!collideWhileMovingY(figure))  //if the figure does not collide , it falls
		figure->moveFigureY();
	else { //if the figure collides , figure individual blocks are added to the idle list and new random blocks generated
		startIdleCounter();
	}
}

void TetrisBoard::startIdleCounter(){
	if (!idleCounter)
		iCounter=0;
	idleCounter=true;
}

bool TetrisBoard::getIdleCounter(){
	iCounter=Min(iCounter+3,30);

	if (key[KEY_LEFT] || key[KEY_RIGHT])
		iCounter-=2;

	if ((iCounter>20) && (idleCounter)){
		idleCounter=false;
		return true;
	}
	return false;


}
void TetrisBoard::increaseFallRate(){

	figure->increaseFallRate();
}

void TetrisBoard::moveFigureX(bool pos){
	if (!targetLocked)
		if (!collideWhileMovingX(pos))
			figure->moveFigureX(pos);
}


bool TetrisBoard::collideWhileMovingY(Figure* f){
	
	for (list<Block>::iterator p=idleBlocks.begin(); p!=idleBlocks.end(); ++p){
		 for (int i=0;i<4;i++){
			 if (( ( f->getY(i)+blockSize+f->getFallRate(i) ) >= ( p->getY() ) 
				 &&  ( f->getY(i)+blockSize+f->getFallRate(i) <= ( p->getY()+blockSize )))
				 && (f->getX(i)<=(p->getX()+blockSize-1) && (f->getX(i)>=(p->getX())))) { //if moving blocks Y + blocksize + fallRate = idle block Y then we have a collision or if it has reached the bottom line
					
						f->setCoordinates((f->getY(i)+blockSize-p->getY())); // fs current y = (y - ( fs' y + blocksize - idle blocks' y)) , lookup f->setCoordinates() definition
				return true;	
			 }
	    }
	}

	for (int i=0;i<4;i++) 
		 if	(f->getY(i)+f->getFallRate(i)>=(buffer->h-blockSize)) {//first collision, without any idle blocks
			f->setCoordinates((f->getY(i)-(buffer->h-blockSize-1)));
				return true;
		 }
	
	return false;
}

BITMAP* TetrisBoard::getScoreBuffer(){

	return score->getScoreBuffer();

}

bool TetrisBoard::collideWhileMovingX(bool pos){

	if (pos){
	for (list<Block>::iterator p=idleBlocks.begin(); p!=idleBlocks.end(); ++p){
		 for (int i=0;i<4;i++)
			 if (( ( ( ( figure->getX(i) )<=p->getX()+blockSize) 
				  && ( ( figure->getX(i)>=p->getX() ) ) )  // (if moving blocks X -1 = idle blockX  OR  moving blocks X+blocksize+1 = idle block X )
			      && (( (figure->getY(i)<=p->getY() )
				  && ((figure->getY(i)+blockSize-1)>=p->getY() )) 
				  || ( (figure->getY(i)>=p->getY() )
				  && ((figure->getY(i))<=(p->getY()+blockSize-3) )) ))
				  || (figure->getX(i)<=2))//AND Moving block bottom Y >= idle block top Y
				return true;
	}
	
	}
	else{
	for (list<Block>::iterator p=idleBlocks.begin(); p!=idleBlocks.end(); ++p){
		 for (int i=0;i<4;i++)
			 if (( ( ( ( figure->getX(i)+blockSize )>=p->getX()) 
				 && ( ( figure->getX(i)<=p->getX() ) ) )  // (if moving blocks X -1 = idle blockX  OR  moving blocks X+blocksize+1 = idle block X )
			      && ( (figure->getY(i)<=p->getY() ) 
				  && (((figure->getY(i)+blockSize-1)>=p->getY() )) 
				  || ( (figure->getY(i)>=p->getY() )
				  && ((figure->getY(i))<=(p->getY()+blockSize-3) )) ))
				  || (figure->getX(i)>= ((blockWidth-1)*blockSize) )) //AND Moving block bottom Y >= idle block top Y
				return true;
	}

	}

	return false;

}

void TetrisBoard::AddFigureToIdle(){

	sfx->idleSFX();

	 for (int i=0;i<4;i++){
		 map[figure->getY(i)/blockSize][figure->getX(i)/blockSize]=true;
		 idleBlocks.push_back(figure->getFigure(i));
	 }
	 checkLinesFromBellow();
}

//check for a complete line
void TetrisBoard::checkLinesFromBellow(){ 
	
	int lineCheck=0;

	for (int i=blockHeight-challengeModeLines-1;i>=0;i--){
		lineCheck=0;

		for (int j=0;j<blockWidth;j++){
			if (map[i][j]==true)
				lineCheck++;
			else 
				break;
		}
		if (lineCheck==blockWidth){
			if(!Line->isAnimating()){
				if (score->isAnimating()) score->abort();
				score->setLine(i); //set line to begin point animation
				setLines(); //for the line class
			}
				destroyLine(i);
				i++;
				if (gameMode==1 && challengeModeLines>0){
					challengeModeLines--;
					lowerLines++;
				
				}
		}
		
	}
	if (gameMode==1)
		destroyLowerLines();

}

void TetrisBoard::destroyLowerLines(){

	for (int i=0;i<lowerLines;i++){
		destroyLine(blockHeight-1);
		Line->setLine(blockHeight-1-i);
	}
	lowerLines=0;
}


void TetrisBoard::setLines(){

	Line->pauseAnimation();
	getIdleBuffer();
	//set buffer to animate
	Line->setBuffer(buffer);
		
	Line->startAnimation();
	
	//get lines for the animation
	int lineCheck=0;	
	for (int i=blockHeight-challengeModeLines-1;i>=0;i--){
		lineCheck=0;
		for (int j=0;j<blockWidth;j++){
			if (map[i][j]==true)
				lineCheck++;
			else 
				break;
		}
			if (lineCheck==blockWidth){
				Line->setLine(i);
				score->addLine();
			}
			
	}
	//play a sound for the line destruction
	sfx->lineSFX();
}

void TetrisBoard::destroyLine(int line){
	//reset rising blocks timer (only in challenge mode)
	timePassed=0;
	incrementBlocks=false;

	//remove blocks of the line parameter
	list<Block>::iterator p = idleBlocks.begin();
	while(p != idleBlocks.end()){  //erase the blocks of the current line 
	
		if (( p->getY()/blockSize)==line ){
			//send each color to the score class to define final score
			score->setColors(p->getColor());
			p=idleBlocks.erase(p);

		}		
		else p++;
	 }
	
	//update the upper lines
	for (list<Block>::iterator p=idleBlocks.begin(); p!=idleBlocks.end(); ++p){  
	
		 if (( p->getY()/blockSize)<line ){
			 p->setY(blockSize);
		 }
	}

	//erase the blocks of the current line and update the upper lines in the bool map
    for (int i=line;i>0;i--)
		for (int j=0;j<blockWidth;j++)
			map[i][j]=map[i-1][j];
			
}

BITMAP* TetrisBoard::getFallingBlocksBuffer(){
	Line->animateFallingPieces();

	return (Line->getFallingBuffer());
}

void TetrisBoard::moveBlocksAbove(){

	for (list<Block>::iterator p=idleBlocks.begin(); p!=idleBlocks.end(); ++p){  
			p->setY(-blockSize);

		 }

	for (int i=0;i<blockHeight-1;i++)
		for (int j=0;j<blockWidth;j++)
			map[i][j]=map[i+1][j];
		
	for (int j=0;j<blockWidth;j++)
			map[blockHeight-1][j]=true;

	for (int i=0;i<blockWidth;i++){
		Block* block;
		block = new Block(i*blockSize,(blockHeight-1)*blockSize);
		idleBlocks.push_back(*block);
		delete block;
	}
}

BITMAP* TetrisBoard::getIdleBuffer(){ //Draws all the idle blocks onto a buffer

	//true if there is a line destruction 		
	if (Line->isAnimating()) 
		Line->animate(buffer);
	else {
		//Tetris background color
			setBackground();
		for (list<Block>::iterator p=idleBlocks.begin(); p!=idleBlocks.end(); ++p){
			rect(buffer,p->getX()+1,p->getY(),p->getX()+blockSize,p->getY()+blockSize,makecol(255,255,255));
			rectfill(buffer,p->getX()+2,p->getY()+1,p->getX()+blockSize-1,p->getY()+blockSize-1,getColor(p->getColor()));
		}
	}
			
	return buffer;
}

void TetrisBoard::setBackground(){
	clear_to_color(buffer,makecol(0,0,0));  

/*	int counter=0;
	int depth=0;
		for (int i=buffer->h;i>=0;i--){
			counter++;
			if (counter==8){
				
				depth++;
				counter=0;
			}
			hline(buffer,0,i,buffer->h,makecol(depth,depth,depth));
		}*/
}

bool TetrisBoard::isPointAnimating(){

	return score->isAnimating();

}
		
BITMAP* TetrisBoard::getPointBuffer(){

	return score->getPointBuffer();

}

//Draws all the moving blocks of the figure onto the buffer
BITMAP* TetrisBoard::getMovingBuffer(bool showGrid){
	

	for (int i=0;i<4;i++){
				rect(buffer,figure->getX(i)+1,figure->getY(i),
				figure->getX(i)+blockSize,figure->getY(i)+blockSize,makecol(255,255,255));
				rectfill(buffer,figure->getX(i)+2,figure->getY(i)+1,
				figure->getX(i)+blockSize-1,figure->getY(i)+blockSize-1,getColor(figure->getColor(i)));
	}

	if (showGrid)
		showHelpGrid();

	return buffer;
}


//if the blocks have reached the upper line
bool TetrisBoard::overFlow(){

	for (int i=0;i<blockWidth;i++)
		if (map[1][i]){
			//std::cout<<"overflow";
			return true;
		}

	return false;
}

int TetrisBoard::getColor(int color){

	switch (color){
	case 0:
		return makecol(255, 102, 0); //orange
	case 1:
		return makecol(125, 189, 0); //green
	case 2:
		return makecol(41, 86, 178); //blue
	case 3:
		return makecol(150,150,0);
	case 4:
		return makecol(220, 246, 0); //yellow
	case 5:
		return makecol(150,80,0); 
	case 6:
		return makecol(150,0,150); //purple
	case 7:
		return makecol(101,156,239); //cornflower blue
	case 8:
		return makecol(165, 42, 42); //red
	case 9:
		return makecol(102, 102, 102); //gray
	default:
		return makecol(255,0,0);
	}
}

void TetrisBoard::setTransparentBlock(int color){
	clear_to_color(transBlock,makecol(0,0,0));

	BITMAP* tempblock;
	tempblock=create_bitmap(19,19);
	clear_to_color(tempblock,getColor(color));

	draw_trans_sprite(transBlock,tempblock,0,0);;

	destroy_bitmap(tempblock);

}


void TetrisBoard::rotateFigure(bool clockwise){

	if(!targetLocked){
		figure->rotation(clockwise);

		if (collideWhileRotating()){
			figure->rotation(!clockwise);
		}
		else 
			sfx->rotationSFX();
	}
}

bool TetrisBoard::collideWhileRotating(){
	
	for (list<Block>::iterator p=idleBlocks.begin(); p!=idleBlocks.end(); ++p){
		 for (int i=0;i<4;i++){
			  if ( ( ( ( (figure->getX(i) ) >= p->getX()) && (figure->getX(i) <= (p->getX()+blockSize-1) ) ) /////{  [ }  ] from right to left
				||  ( ( (figure->getX(i) ) <= p->getX()) && ((figure->getX(i)+blockSize-1) >= p->getX() ) ) )/////[  {  ]  } from left to right
				&& ( ( (figure->getY(i) ) <= p->getY()) && ((figure->getY(i)+blockSize) >= p->getY() ) )///from above
				|| ( ((figure->getY(i))>=p->getY()) && (figure->getY(i)<=p->getY()+blockSize-6) && figure->getX(i)==p->getX()) //from bellow
				|| ( figure->getY(i)>=(buffer->h-blockSize) )) //bottom yoffSet
			   return true;
			  else if ( figure->getX(i)>= ((blockWidth-1)*blockSize)+1 ){  // right xoffSet
				figure->moveFigureX(true);
				if (collideWhileRotating()){
					figure->moveFigureX(false);
					return true;
				}
				return false;
			  }
			  else if (figure->getX(i)<=-1)  {//left xoffset
				figure->moveFigureX(false);
				if (collideWhileRotating()){
					figure->moveFigureX(true);
					return true;
				}
				if (typeid(*figure)==typeid(Figure2)){ //figure 2 left offset handler
					if (collideWhileRotating()){
						figure->moveFigureX(true);
						return true;
					}
				}
				return false;
			  }
		 }
	}

	return false;
	
}

void TetrisBoard::showHelpGrid(){

	Figure* temp;

	temp=getFigure(figure);
	temp->initialize();

	for(int i=0;i<4;i++)
		temp->setFigure(figure->getFigure(i),i);

	temp->setColor(figure->getColor(0));
	temp->targetLocked();
	setTransparentBlock(temp->getColor(0));

	while (!collideWhileMovingY(temp))
		temp->moveFigureY();

		for (int i=0;i<4;i++){
				rect(buffer,temp->getX(i)+1,temp->getY(i),
				temp->getX(i)+blockSize,temp->getY(i)+blockSize,makecol(80,80,80));
				draw_trans_sprite(buffer,transBlock,temp->getX(i)+1,temp->getY(i)+1);
		}

	delete temp;
	
	
	//old helpGrid
	//*******
	/*bool flag;
	for (int i=0;i<4;i++){
		flag=false;
		for (int j=(figure->getY(i)/blockSize);j<=blockHeight;j++)
			if (map[j][(figure->getX(i)/blockSize)]){
				rectfill(buffer,(figure->getX(i))+blockSize/2-1,j*blockSize-4,(figure->getX(i))+blockSize/2+3,j*blockSize-2,makecol(255,0,0));	
				flag=true;
				break;
			}
		if (!flag)
				rectfill(buffer,(figure->getX(i))+blockSize/2-1,blockSize*blockHeight-4,(figure->getX(i))+blockSize/2+3,blockSize*blockHeight-2,makecol(255,0,0));	
	}*/
		
}


void TetrisBoard::aSecondChance(){
	if (secondChance){
		for  (int i=0;i<4;i++)
			Line->isAFallingPiece(figure->getX(i)+20,figure->getY(i),true);
		Line->blocksAreFalling(4);
		setMovingFigure(holdFigure);
		setHoldFigure();
		secondChance=false;
		secondChanceCounter=0;
	}
 

}