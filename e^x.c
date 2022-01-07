#include<stdio.h>
#include<math.h>
#include<pthread.h>
#define APPR 150
	
double powr[APPR], fact[APPR], x, sum_ = 0;

double factorial(double num){
	if(num <= 1) return 1;
	return num*factorial(num-1);
}

void* power(void* arg){
	int i;
	for(i = 0; i < APPR; i++){
		powr[i] = pow(x, i+1);
	}
	return powr;
}
void* facto(void* arg){
	int i;
	for(i = 0; i < APPR; i++){
		fact[i] = factorial(i+1);
	}
	return fact;
}
void* sum(void* arg){
	int i;
	for(i = 0; i < APPR; i++){
		sum_ += (powr[i] / fact[i]);
	}
	sum_++;
	
}
int main(){
		x = 4;   //e^4 = ?
		pthread_t thread[3];
		pthread_create(&thread[0], NULL, power, NULL);
		pthread_create(&thread[1], NULL, facto, NULL);
		pthread_join(thread[0], NULL);
		pthread_join(thread[1], NULL);
		pthread_create(&thread[2], NULL, sum, NULL);
		pthread_join(thread[2], NULL);
		printf("%lf", sum_);
		
}

