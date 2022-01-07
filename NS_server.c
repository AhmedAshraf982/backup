#include <stdio.h>    
#include <stdlib.h>      
#include <unistd.h>
#include <sys/types.h>   
#include <sys/wait.h>
#include <sys/shm.h>    
#include <errno.h>     
#include <semaphore.h>    
#include <fcntl.h>
#define SIZE 10  //let the string be of size 10
int main (){
    int i;                     
    int shmkey;           
    int shmid;                
    sem_t *sem;                 
    pid_t pid;                  
    int *p;                     
    int sCount;

    shmkey = 1122;
	shmid = shmget (shmkey, sizeof (int), 0644 | IPC_CREAT);
    if (shmid < 0){                       
        perror ("shmget\n");
        exit (1);
    }
	p = (int *) shmat (shmid, NULL, 0);  
	sem = sem_open ("pSem", O_CREAT | O_EXCL, 0644, 1);
	sem_unlink ("pSem");     
	for(i = 0; i < SIZE; i++){
		int bit = i % 2;  //either 0 or 1
		*(p+i) = bit + '0';   //typecasting to character
	}
	sleep(3);
	sem_wait (sem);
	printf("Process 1 starts taking 1's compliment:\n");
	//taking 1's compliment
	for(i = 0; i < SIZE; i++){
		if(*(p+i) == '0'){
			*(p+i) = '1';
		}else{
			*(p+i) = '0';
		}
	}
	for(i = 0; i < SIZE; i++){
		printf("%c ", *(p+i));
	}
	sem_post (sem);
}
