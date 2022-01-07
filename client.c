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
	int num = *s - '0';
	printf("Number by the server: %d\n", num);
	*shm = 'r';
	int i;
	int val;
	for(i = 1; i <= 10; i++){
		while(*shm != '*')
			sleep(1);
		printf("Server types: *");
		val = i*num;
		*shm = val + '0';
	}
	exit(0);
}
