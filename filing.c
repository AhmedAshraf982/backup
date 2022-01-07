#include<stdio.h>

struct vaccine{
	char name[20];
	char code[3];
	int initial;
	int dos;
};
int main(){
	FILE *file;
	struct vaccine vc;
//	scanf("%s", &vc.name);
//	scanf("%s", &vc.code);
//	scanf("%d", &vc.initial);
//	scanf("%d", &vc.dos);
	file = fopen("check.txt", "rb");
//	fwrite(&vc, sizeof(vc), 1, file);	
	fread(&vc, sizeof(vc), 1, file);
	printf("%s", vc.code);
}
