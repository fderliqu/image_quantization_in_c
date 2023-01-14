#include<stdio.h>
#include<string.h>
#include<stdlib.h>

/*
*	getFileExtention : get file extention
*
*	PARAM : 
*		char c : the n-2 index of file name
* 	RETURN :
*		1 if the file is .ppm
*		2 i the file is .pgm
*		0 otherwise
*/
int getFileExtention(char c){
	int status;
	switch (c)
	{
	case 'p':
		status = 1;
		
		break;
	case 'g':
		status = 2;
		break;
	default:
		status = 0;
		break;
	}
	return status;
}

int main(int argc, char const *argv[])
{
	if( argc < 3)return -1;
	/*
	*On recupère la taille des chaine de caractère des arguments
	*/
	size_t size_input = strlen(argv[1]);
	size_t size_output = strlen(argv[2]);
	/*ON regarde si on s'est pas trompé sur les extensions*/
	if(getFileExtention(argv[1][size_input-2]) != getFileExtention(argv[2][size_output-2])){
		printf("input and output not the same extention file\n");
		return -1;
	}
	unsigned char ch;
	int n;
	/*choix de n*/
	printf("Quantization number (between 0 and 255) : ");
	scanf("%d",&n);
	/*Ouverture des fichiers */
	FILE * fd_input = fopen(argv[1],"r");
	FILE * fd_output = fopen(argv[2],"w");
	if(fd_input == NULL || fd_output == NULL){
		printf("Cannot read the file\n");
		return -1;
	}
	/*tmp_count compte le nombre de fois qu'il y a un retour là la ligne*/
	int tmp_count = 0;
	do{
		ch = fgetc(fd_input);
		/*si on est dans l'entete, on recopie l'entete*/
		if(tmp_count<3)fprintf(fd_output,"%c",ch);
				/*si on est a la quatrieme ligne, debut des dates, on applique la quantification*/
		if(tmp_count >= 3){
			fprintf(fd_output,"%c",(ch/n)*n);
		}
		/*si retour a la ligne on incremente tmp_count*/
		if(ch == 10)tmp_count++;

	}while(!feof(fd_input));
	fclose(fd_input);
	fclose(fd_output);
	return 0;
}