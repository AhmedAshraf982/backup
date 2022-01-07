#include<stdio.h>
int main(){
	char first_letter = ' ', second_letter = ' ';
	printf("Enter number of characters: ");
	int num;
	scanf("%d", &num);
	printf("Enter first character: ");
	fflush(stdin);
	scanf("%c", &first_letter);
	if(num == 2){
		printf("Enter second character: ");
		fflush(stdin);
    	scanf("%c", &second_letter);
	}
	int value = 0;
	switch(first_letter){
		case 'I':{
			value += 1;
			break;
		}
		case 'V':{
			value += 5;
			break;
		}
		case 'X':{
			value += 10;
			break;
		}
		case 'L':{
			value += 50;
			break;
		}
		case 'C':{
			value += 100;
			break;
		}
		case 'D':{
			value += 500;
			break;
		}
		case 'M':{
			value += 1000;
			break;
		}
	}
	if(num == 2){
		switch(second_letter){
		case 'I':{
			if(value >= 1){
				value += 1;
			}else{
				value -= 1;
			}
			break;
		}
		case 'V':{
			if(value >= 5){
				value += 5;
			}else{
				value -= 5;
			}
			break;
		}
		case 'X':{
			value += 10;
			break;
		}
		case 'L':{
			if(value >= 50){
				value += 50;
			}else{
				value -= 50;
			}
			break;
		}
		case 'C':{
			if(value >= 100){
				value += 100;
			}else{
				value -= 100;
			}
			break;
		}
		case 'D':{
			if(value >= 500){
				value += 500;
			}else{
				value -= 500;
			}
			break;
		}
		case 'M':{
			if(value >= 1000){
				value += 1000;
			}else{
				value -= 1000;
			}
			break;
		}
	}
	}
	if(value < 0){
		value *= -1;
	}
	printf("%c%c =  %d in integer.", first_letter, second_letter, value);
}
