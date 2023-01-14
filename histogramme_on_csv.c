#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define INT_NUMBER 256
#define OUTPUT_FD "histogramme.csv"

int main(int argc, char const *argv[])
{
	if( argc < 2)return -1;
	unsigned char ch;
	int n;
	int * histogramme = (int *) calloc( INT_NUMBER, sizeof(int) );
	FILE * fd_input = fopen(argv[1],"r");
	FILE * fd_output = fopen(OUTPUT_FD,"w");
	if(fd_input == NULL || fd_output == NULL){
		printf("Cannot read the file\n");
		return -1;
	}
	int tmp_count = 0;
	do{
		ch = fgetc(fd_input);
		if(tmp_count >= 3){
			histogramme[ch]++;
		}
		if(ch == 10)tmp_count++;

	}while(!feof(fd_input));
	fclose(fd_input);
	for(int i=0;i<INT_NUMBER;i++){
		fprintf(fd_output,"%d,%d\n",i,histogramme[i]);
	}
	fclose(fd_output);
	free(histogramme);
	return 0;
}