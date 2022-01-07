#include<stdio.h>
#include<pthread.h>
#include<time.h>

void insertionSort(int* array, int size){  //ascending order
	int x, y;
	for(x = 0; x < size-1; x++){
		int key = array[x+1];
		y = x;
		while(key < array[y] && y >= 0){
			array[y+1] = array[y];
			y--;
		}
		array[y+1] = key;
	}
}
int main(){
//	srand(NULL);
//	int num = 100000;
//	int array[num];
//	int x, y;
//	for(x = 0; x < num; x++){
//		array[x] = rand()%1000;
//	}
//	insertionSort(&array, num);
//printf("*\n* *\n* * *\n* * * *");


printf("*\n*\t*\n*\t*\t*\n*\t*\n*");

int num;
printf("Enter an integer: ");
scanf("%d", &num);
printf("You entered:%9d", num);
//	for(x = 0; x < num; x++){
//		printf("%d ", array[x]);
//	}
}
