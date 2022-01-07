#include<stdio.h>
#include<time.h>
void student(float marks[], int size){
	float mean = 0;
	int x;
	for(x = 0; x < size; x++){
		mean += marks[x];
	}
	mean /= size;
	printf("%f", mean);
}

int sum_array(int array[], int size){
	int sum,x;
	for (x=0 ; x<size ; x++){
    	sum += array[x];
	}
	return sum;
}
    
int main(){
//	srand(time(NULL));
//	int num = 5;
//	int arr[num];
//	int x;
//	for(x = 0; x < num; x++){
//		arr[x] = rand()%200;
////		printf("%d\n", arr[x]);
//  }
//	int max = arr[0];
//	for(x = 1; x < num; x++){
//		if(arr[x] > max){
//			max = arr[x];
//		}
//	}
////	printf("max: %d", max);
//	float price_of_milk = 120;
//	float price_of_biscuits = 200;
//	float bill = 0;
//	float num_of_kgs_milk = 2.5;
//	float num_of_kgs_biscuits = 3.7;
//	bill = num_of_kgs_milk*price_of_milk + num_of_kgs_biscuits*price_of_biscuits;
//	printf("%.0f", bill);
    int sum,x;
    int size = 10;
    int arr[size];
    for (x=0 ; x <size ; x++){
    	arr[x]=x;
	}
	sum = sum_array(arr, size);
    printf("%d", sum);
}


