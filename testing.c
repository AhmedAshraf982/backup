#include<stdio.h>

int main(){
	int num1, num2, num3, num4;
	num1 = 14;
	num2 = 5;
	num3 = 70;
	num4 = 100;
	int hold;
	if(num1 > num2){
		hold = num1;
	}else{
		hold = num2;
	}
	if(num3 > hold){
		hold = num3;
	}
	if(num4 > hold){
		hold = num4;
	}
	printf("%d", hold);
}

