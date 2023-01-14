#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define INT_NUMBER 256

int main(int argc, char const *argv[])
{
	if( argc < 2)return -1;
	unsigned char ch;
	int * histogramme = (int *) calloc( INT_NUMBER, sizeof(int) );
	FILE * fd_input = fopen(argv[1],"r");
	if(fd_input == NULL){
		printf("Cannot read the file\n");
		return -1;
	}
	int tmp_count = 0;
	do{
		ch = fgetc(fd_input);
		if(tmp_count >= 3){
			if(!feof(fd_input))histogramme[ch]++;
		}
		if(ch == 10)tmp_count++;
	}while(!feof(fd_input));
	fclose(fd_input);
	printf("Value\tNumber of iteration\n");
	for(int i=0;i<INT_NUMBER;i++){
		printf("%d\t%d\n",i,histogramme[i]);
	}
	free(histogramme);
	return 0;
}