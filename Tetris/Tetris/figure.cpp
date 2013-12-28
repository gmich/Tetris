#include "figure.h"

Figure::Figure(){

	figure[0].setX(blockSize*((blockWidth-2)/2));
	figure[0].setY(0);

	figure[1].setX(blockSize*((blockWidth-2)/2));
	figure[1].setY(0);

	figure[2].setX(blockSize*((blockWidth-2)/2));
	figure[2].setY(0);

	figure[3].setX(blockSize*((blockWidth-2)/2));
	figure[3].setY(0);

	state = 1;

	setColor(rand()%9);

}


//////////////////////
//////////////////////
////////[ ][ ]////////
////////[ ][ ]////////
//////////////////////
//////////////////////

void Figure1::initialize(){

	figure[0].setX(0);
	figure[0].setY(0);

	figure[1].setX(0);
	figure[1].setY(blockSize);

	figure[2].setX(blockSize);
	figure[2].setY(0);

	figure[3].setX(blockSize);
	figure[3].setY(blockSize);


}

void Figure1::rotation(int clockWise){;}





//////////////////////
////////[ ]///////////
////////[ ]///////////
////////[ ]///////////
////////[ ]///////////
//////////////////////

void Figure2::initialize(){

	figure[0].setX(blockSize);
	figure[0].setY(0);

	figure[1].setX(blockSize);
	figure[1].setY(blockSize);

	figure[2].setX(blockSize);
	figure[2].setY(2*(blockSize));

	figure[3].setX(blockSize);
	figure[3].setY(3*(blockSize));

}

void Figure2::rotation(int clockWise){

	
	if (clockWise){

		switch (state){

			case 1:

				figure[0].setX(-2*blockSize);
				figure[0].setY(2*blockSize);

				figure[1].setX(-blockSize);
				figure[1].setY(blockSize);

				figure[2].setX(0);
				figure[2].setY(0);

				figure[3].setX(blockSize);
				figure[3].setY(-blockSize);
	
				state=2;

				break;
			
			case 2:

				figure[0].setX(2*blockSize);
				figure[0].setY(-2*blockSize);

				figure[1].setX(blockSize);
				figure[1].setY(-blockSize);

				figure[2].setX(0);
				figure[2].setY(0);

				figure[3].setX(-blockSize);
				figure[3].setY(blockSize);
				state=1;

				break;

		}

	}
	else{
		switch (state){

			case 1:

				figure[0].setX(-2*blockSize);
				figure[0].setY(2*blockSize);

				figure[1].setX(-blockSize);
				figure[1].setY(blockSize);

				figure[2].setX(0);
				figure[2].setY(0);

				figure[3].setX(blockSize);
				figure[3].setY(-blockSize);
	
				state=2;

				break;
			
			case 2:

				figure[0].setX(2*blockSize);
				figure[0].setY(-2*blockSize);

				figure[1].setX(blockSize);
				figure[1].setY(-blockSize);

				figure[2].setX(0);
				figure[2].setY(0);

				figure[3].setX(-blockSize);
				figure[3].setY(blockSize);
				state=1;

				break;

		}

	}

			
}





//////////////////////
//////////////////////
////////[ ]///////////
/////[ ][ ][ ]////////
//////////////////////
//////////////////////


void Figure3::initialize(){

	figure[0].setX(0);
	figure[0].setY(blockSize);

	figure[1].setX(blockSize);
	figure[1].setY(0);

	figure[2].setX(blockSize);
	figure[2].setY(blockSize);

	figure[3].setX(2*blockSize);
	figure[3].setY(blockSize);


}

void Figure3::rotation(int clockWise){
	
	if (clockWise){

		switch (state){

			case 1:

				figure[0].setX(blockSize);
				figure[0].setY(blockSize);

				figure[1].setX(0);
				figure[1].setY(0);

				figure[2].setX(0);
				figure[2].setY(0);

				figure[3].setX(0);
				figure[3].setY(0);
	
				state=2;

				break;
			
			case 2:

				figure[0].setX(0);
				figure[0].setY(0);

				figure[1].setX(-blockSize);
				figure[1].setY(+blockSize);

				figure[2].setX(0);
				figure[2].setY(0);

				figure[3].setX(0);
				figure[3].setY(0);

				state=3;

				break;

			case 3:

				figure[0].setX(0);
				figure[0].setY(0);

				figure[1].setX(0);
				figure[1].setY(0);

				figure[2].setX(0);
				figure[2].setY(0);

				figure[3].setX(-blockSize);
				figure[3].setY(-blockSize);

				state=4;

				break;

			case 4:

				figure[0].setX(-blockSize);
				figure[0].setY(-blockSize);

				figure[1].setX(+blockSize);
				figure[1].setY(-blockSize);

				figure[2].setX(0);
				figure[2].setY(0);

				figure[3].setX(+blockSize);
				figure[3].setY(+blockSize);
				state=1;

				break;
		}

	}
	else{
		switch (state){

			case 1:

				figure[0].setX(+blockSize);
				figure[0].setY(+blockSize);

				figure[1].setX(-blockSize);
				figure[1].setY(+blockSize);

				figure[2].setX(0);
				figure[2].setY(0);

				figure[3].setX(-blockSize);
				figure[3].setY(-blockSize);
	
				state=4;

				break;
			
			case 2:

				figure[0].setX(-blockSize);
				figure[0].setY(-blockSize);

				figure[1].setX(0);
				figure[1].setY(0);

				figure[2].setX(0);
				figure[2].setY(0);

				figure[3].setX(0);
				figure[3].setY(0);

				state=1;

				break;

			case 3:

				figure[0].setX(0);
				figure[0].setY(0);

				figure[1].setX(+blockSize);
				figure[1].setY(-blockSize);

				figure[2].setX(0);
				figure[2].setY(0);

				figure[3].setX(0);
				figure[3].setY(0);

				state=2;

				break;

			case 4:

				figure[0].setX(0);
				figure[0].setY(0);

				figure[1].setX(0);
				figure[1].setY(0);

				figure[2].setX(0);
				figure[2].setY(0);

				figure[3].setX(+blockSize);
				figure[3].setY(+blockSize);
	
				state=3;

				break;

		}

	}
	


}




//////////////////////
//////////////////////
////////[ ][ ]////////
/////[ ][ ]///////////
//////////////////////
//////////////////////

void Figure4::initialize(){

	figure[0].setX(0);
	figure[0].setY(blockSize);

	figure[1].setX(blockSize);
	figure[1].setY(0);

	figure[2].setX(blockSize);
	figure[2].setY(blockSize);

	figure[3].setX(2*blockSize);
	figure[3].setY(0);


}

void Figure4::rotation(int clockWise){
	
	if (clockWise){

		switch (state){

			case 1:

				figure[0].setX(2*blockSize);
				figure[0].setY(0);

				figure[1].setX(0);
				figure[1].setY(0);

				figure[2].setX(0);
				figure[2].setY(0);

				figure[3].setX(0);
				figure[3].setY(2*blockSize);
	
				state=2;

				break;
			
			case 2:

				figure[0].setX(-2*blockSize);
				figure[0].setY(0);

				figure[1].setX(0);
				figure[1].setY(0);

				figure[2].setX(0);
				figure[2].setY(0);

				figure[3].setX(0);
				figure[3].setY(-2*blockSize);

				state=1;

				break;

		
		}

	}
	else{
		switch (state){

			case 1:

				figure[0].setX(2*blockSize);
				figure[0].setY(0);

				figure[1].setX(0);
				figure[1].setY(0);

				figure[2].setX(0);
				figure[2].setY(0);

				figure[3].setX(0);
				figure[3].setY(2*blockSize);
	
				state=2;

				break;
			
			case 2:

				figure[0].setX(-2*blockSize);
				figure[0].setY(0);

				figure[1].setX(0);
				figure[1].setY(0);

				figure[2].setX(0);
				figure[2].setY(0);

				figure[3].setX(0);
				figure[3].setY(-2*blockSize);

				state=1;

				break;

		
		}

	}
	


}



//////////////////////
//////////////////////
/////[ ][ ]///////////
////////[ ][ ]/////////
//////////////////////
//////////////////////

void Figure5::initialize(){

	figure[0].setX(0);
	figure[0].setY(0);

	figure[1].setX(blockSize);
	figure[1].setY(0);

	figure[2].setX(blockSize);
	figure[2].setY(blockSize);

	figure[3].setX(2*blockSize);
	figure[3].setY(blockSize);


}

void Figure5::rotation(int clockWise){
	
	if (clockWise){

		switch (state){

			case 1:

				figure[0].setX(blockSize);
				figure[0].setY(2*blockSize);

				figure[1].setX(blockSize);
				figure[1].setY(0);

				figure[2].setX(0);
				figure[2].setY(0);

				figure[3].setX(0);
				figure[3].setY(0);
	
				state=2;

				break;
			
			case 2:

				figure[0].setX(-blockSize);
				figure[0].setY(-2*blockSize);

				figure[1].setX(-blockSize);
				figure[1].setY(0);

				figure[2].setX(0);
				figure[2].setY(0);

				figure[3].setX(0);
				figure[3].setY(0);

				state=1;

				break;

		
		}

	}
	else{
		switch (state){

		case 1:

				figure[0].setX(blockSize);
				figure[0].setY(2*blockSize);

				figure[1].setX(blockSize);
				figure[1].setY(0);

				figure[2].setX(0);
				figure[2].setY(0);

				figure[3].setX(0);
				figure[3].setY(0);
	
				state=2;

				break;
			
			case 2:

				figure[0].setX(-blockSize);
				figure[0].setY(-2*blockSize);

				figure[1].setX(-blockSize);
				figure[1].setY(0);

				figure[2].setX(0);
				figure[2].setY(0);

				figure[3].setX(0);
				figure[3].setY(0);

				state=1;

				break;

		
		}

	}
	
}


//////////////////////
////////[ ][ ]////////
////////[ ]///////////
////////[ ]///////////
//////////////////////
//////////////////////


void Figure6::initialize(){

	figure[0].setX(blockSize);
	figure[0].setY(0);

	figure[1].setX(blockSize);
	figure[1].setY(blockSize);

	figure[2].setX(blockSize);
	figure[2].setY(2*blockSize);

	figure[3].setX(2*blockSize);
	figure[3].setY(0);


}

void Figure6::rotation(int clockWise){
	
	if (clockWise){

		switch (state){

			case 1:

				figure[0].setX(0);
				figure[0].setY(0);

				figure[1].setX(-blockSize);
				figure[1].setY(-blockSize);

				figure[2].setX(+blockSize);
				figure[2].setY(-blockSize);

				figure[3].setX(0);
				figure[3].setY(0);
	
				state=2;

				break;
			
			case 2:

				figure[0].setX(0);
				figure[0].setY(0);

				figure[1].setX(blockSize);
				figure[1].setY(blockSize);

				figure[2].setX(-blockSize);
				figure[2].setY(blockSize);

				figure[3].setX(-2*blockSize);
				figure[3].setY(+2*blockSize);

				state=3;

				break;

			case 3:

				figure[0].setX(blockSize);
				figure[0].setY(blockSize);

				figure[1].setX(0);
				figure[1].setY(0);

				figure[2].setX(-blockSize);
				figure[2].setY(-blockSize);

				figure[3].setX(0);
				figure[3].setY(-2*blockSize);

				state=4;

				break;

			case 4:

				figure[0].setX(-blockSize);
				figure[0].setY(-blockSize);

				figure[1].setX(0);
				figure[1].setY(0);

				figure[2].setX(+blockSize);
				figure[2].setY(+blockSize);

				figure[3].setX(2*blockSize);
				figure[3].setY(0);
				state=1;

				break;
		}

	}
	else{
		switch (state){

			case 1:

				figure[0].setX(+blockSize);
				figure[0].setY(+blockSize);

				figure[1].setX(0);
				figure[1].setY(0);

				figure[2].setX(-blockSize);
				figure[2].setY(-blockSize);

				figure[3].setX(-2*blockSize);
				figure[3].setY(0);
	
				state=4;

				break;
			
			case 2:

				figure[0].setX(0);
				figure[0].setY(0);

				figure[1].setX(blockSize);
				figure[1].setY(blockSize);

				figure[2].setX(-blockSize);
				figure[2].setY(blockSize);

				figure[3].setX(0);
				figure[3].setY(0);

				state=1;

				break;

			case 3:

				figure[0].setX(0);
				figure[0].setY(0);

				figure[1].setX(-blockSize);
				figure[1].setY(-blockSize);

				figure[2].setX(blockSize);
				figure[2].setY(-blockSize);

				figure[3].setX(2*blockSize);
				figure[3].setY(-2*blockSize);

				state=2;

				break;

			case 4:

				figure[0].setX(-blockSize);
				figure[0].setY(-blockSize);

				figure[1].setX(0);
				figure[1].setY(0);

				figure[2].setX(blockSize);
				figure[2].setY(blockSize);

				figure[3].setX(0);
				figure[3].setY(+2*blockSize);
	
				state=3;

				break;

		}

	}
		
}


//////////////////////
/////[ ][ ]///////////
////////[ ]///////////
////////[ ]///////////
//////////////////////
//////////////////////


void Figure7::initialize(){

	figure[0].setX(0);
	figure[0].setY(0);

	figure[1].setX(blockSize);
	figure[1].setY(0);

	figure[2].setX(blockSize);
	figure[2].setY(blockSize);

	figure[3].setX(blockSize);
	figure[3].setY(2*blockSize);


}

void Figure7::rotation(int clockWise){
	
	if (clockWise){

		switch (state){

			case 1:

				figure[0].setX(2*blockSize);
				figure[0].setY(0);

				figure[1].setX(blockSize);
				figure[1].setY(blockSize);

				figure[2].setX(0);
				figure[2].setY(0);

				figure[3].setX(-blockSize);
				figure[3].setY(-blockSize);
	
				state=2;

				break;
			
			case 2:

				figure[0].setX(0);
				figure[0].setY(2*blockSize);

				figure[1].setX(-blockSize);
				figure[1].setY(+blockSize);

				figure[2].setX(0);
				figure[2].setY(0);

				figure[3].setX(blockSize);
				figure[3].setY(-blockSize);

				state=3;

				break;

			case 3:

				figure[0].setX(-2*blockSize);
				figure[0].setY(0);

				figure[1].setX(-blockSize);
				figure[1].setY(-blockSize);

				figure[2].setX(0);
				figure[2].setY(0);

				figure[3].setX(blockSize);
				figure[3].setY(blockSize);

				state=4;

				break;

			case 4:

				figure[0].setX(0);
				figure[0].setY(-2*blockSize);

				figure[1].setX(+blockSize);
				figure[1].setY(-blockSize);

				figure[2].setX(0);
				figure[2].setY(0);

				figure[3].setX(-blockSize);
				figure[3].setY(+blockSize);
				state=1;

				break;
		}

	}
	else{
		switch (state){

			case 1:

				figure[0].setX(0);
				figure[0].setY(2*blockSize);

				figure[1].setX(-blockSize);
				figure[1].setY(+blockSize);

				figure[2].setX(0);
				figure[2].setY(0);

				figure[3].setX(blockSize);
				figure[3].setY(-blockSize);
	
				state=4;

				break;
			
			case 2:

				figure[0].setX(-2*blockSize);
				figure[0].setY(0);

				figure[1].setX(-blockSize);
				figure[1].setY(-blockSize);

				figure[2].setX(0);
				figure[2].setY(0);

				figure[3].setX(blockSize);
				figure[3].setY(blockSize);

				state=1;

				break;

			case 3:

				figure[0].setX(0);
				figure[0].setY(-2*blockSize);

				figure[1].setX(+blockSize);
				figure[1].setY(-blockSize);

				figure[2].setX(0);
				figure[2].setY(0);

				figure[3].setX(-blockSize);
				figure[3].setY(+blockSize);

				state=2;

				break;

			case 4:

				figure[0].setX(2*blockSize);
				figure[0].setY(0);

				figure[1].setX(blockSize);
				figure[1].setY(blockSize);

				figure[2].setX(0);
				figure[2].setY(0);

				figure[3].setX(-blockSize);
				figure[3].setY(-blockSize);
	
				state=3;

				break;

		}

	}
		
}