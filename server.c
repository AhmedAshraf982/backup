#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<stdio.h>
#include<stdlib.h>

#define MAXSIZE 32

void die(char *str) {
	perror(str);
	exit(1);
}

int main(void) {
	char c;
	int shmid;
	key_t key;
	char *shm, *s;

	key = 2211;
	
	if((shmid = shmget(key, MAXSIZE, IPC_CREAT | 0666)) < 0)
		die("shmget");
	if((shm = shmat(shmid, NULL, 0)) == (char*) -1)
		die("shmat");
	s = shm;
	printf("Enter a number: ");
	char num;
	scanf("%c", &num);
	*s = num;
	char arr;
	int index = 0;
	while(*shm != 'r')
		sleep(1);
	printf("Client writes: Ready");
	int i;
	for(i = 1; i < 10; i++){
		scanf("%c", &arr);
		*shm = '*';
		while(*shm == '*')
			sleep(1);
		putchar(*shm);
	}
	exit(0);
}
