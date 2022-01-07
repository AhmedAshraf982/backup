#include<stdio.h>
#include<semaphore.h>
#include<pthread.h>

void thread_function(void* arg){
	int pass_no = (int) arg;
	sem_t lock1, lock2, lock3;
	sem_init(&lock1, 0, 1);
	sem_init(&lock2, 0, 1);
	sem_init(&lock3, 0, 1);
	sem_wait(&lock1);
		printf("Passenger# %d is weighing luggage.\n", pass_no);
		sleep(4);
	sem_post(&lock1);
	sem_wait(&lock2);
		printf("Passenger# %d is being checked for security.\n", pass_no);
		sleep(7);
	sem_post(&lock2);
	sem_wait(&lock3);
		printf("Passenger# %d is getting boarding pass.\n", pass_no);
		sleep(3);
	sem_post(&lock3);
	
}
int main(){
	int num = 10;  //10 people
	pthread_t people[10];
	int x;
	for(x = 0; x < num; x++){
		pthread_create(&people[x], NULL, thread_function, (void*) x);
	}
	for(x = 0; x < num; x++){
		pthread_join(people[x], NULL);
	}
}
