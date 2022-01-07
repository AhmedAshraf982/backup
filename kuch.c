#include<stdio.h>
int main(){
//	int distance[hours];
//	int x;
//	for(x = 0; x < hours; x++){
//		printf("Enter distance# %d: ", x+1);
//		scanf("%d", &distance[x]);
//	}
//	float avg_speed = 0;
//	int total_dist = 0;
//	for(x = 0; x < hours; x++){
//		total_dist = total_dist + distance[x];
//	}


    int hour;//declare
	printf("Enter hours: ");
	scanf("%d", &hour);
	int d1 = 0, d2 = 0, d3 = 0, d4 = 0;
	if(hour > 0){
		scanf("%d", &d1);
	}
	if(hour>1){
		scanf("%d", &d2);
	}
	if(hour>2){
		scanf("%d", &d3);
	}
	if(hour>3){
		scanf("%d", &d4);
	}
	int total = d1+d2+d3+d4;
	float avg_speed = (float)total / (float)hour;
	printf("Avg speed is: %.2f", avg_speed);
}
