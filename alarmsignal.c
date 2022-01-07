#include<stdio.h>
#include<signal.h>

int alarmFlag = 0;
void alarmHandler();

int main(){
	signal(SIGALRM, alarmHandler);
	alarm(5);
	printf("Looping\n");
	while(!alarmFlag){
		pause();
		printf("Loop ends\n");
	}
}
void alarmHandler(){
	printf("An alarm clock signal was received\n");
	alarmFlag = 1;
}
