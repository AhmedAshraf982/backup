#include <stdio.h>
#include<stdlib.h>
int main(){
	char* words[10] = {"orange", "green", "red", "blue", "yellow", "cyan"};
	printf("%p  %p  %p", words, words+1, words+3);
}
