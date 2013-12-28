#include "defines.h"

	int Max(int num1,int num2){
		
		if (num1>num2){
			return num1;
		}
		else if (num1<num2)
			return num2;
		else 
			return num1;
	}

	int Min(int num1,int num2){
		if (num1>num2)
			return num2;
		else if (num1<num2)
			return num1;
		else 
			return num1;
	}