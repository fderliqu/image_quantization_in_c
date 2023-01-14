#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define INT_NUMBER 256
#define GRAYSCALE_FILENAME "tmp_grayscale"

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

/*
*	effectue une conversion d'une image coloré en niveau de gris pour l'histogramme
*/
void grayscaleConversion(char const * filename_input){
	FILE * fd_input = fopen(filename_input,"r");
	FILE * fd_output = fopen(GRAYSCALE_FILENAME,"w");
	if(fd_input == NULL || fd_output == NULL){
		printf("Cannot read the file\n");
		exit(-1);
	}
	int eol_count = 0;
	unsigned char r;
	unsigned char g;
	unsigned char b;
	unsigned char ch;
	do{
		if(eol_count<3){
			ch = fgetc(fd_input);
			if(ch == 10)eol_count++;
		}
		/*Si on arrive à la quatrième ligne, debut des données de l'image*/
		else if(eol_count >= 3){
			r = fgetc(fd_input);
			g = fgetc(fd_input);
			b = fgetc(fd_input);
			/*Ici j'ai effectué seulement la moyenne des 3 valeurs rgb, on aurait pu faire aussi slon la luminosité de l'image*/
			fprintf(fd_output,"%c",(unsigned char)((r+g+b)/3));
		}
	}while(!feof(fd_input));
	fclose(fd_input);
	fclose(fd_output);
}

/*
*	recupère l'histogramme d'un fichier descriptor (le pointeur doit pointer vers le debut des datas)
*/
void setHistogramme(FILE * fd, int * histogramme){
	unsigned char ch;
	do{
		ch = fgetc(fd);
		histogramme[ch]++;
	}while(!feof(fd));
}
/*
*	fonction qui donne la nouvelle valeurs des données selon l'histogramme, le nombre d'intervalles (donnée par l'utilsateur) et la taille de l'image
*/

void setNewValues(int * histogramme, int * newValues, int size[2], int n){
	/*On calcule les nouvelles valeurs de l'image*/
	int limite = (size[0]*size[1])/n;
	int count = 0;
	int value = 0;
	for(int i=0;i<INT_NUMBER;i++){
		count+=histogramme[i];
		newValues[i] = value;
		if(count>limite){
			value = i+1;
			count = 0;
		}
	}
}

/*
*	programme principal : 
*	effectue deux algorthme différents selon l'extention du fichier : 
	si pgm : 
		- On recupère l'histogramme directement
		- on calcule les nouvelles valeurs
		- on met à jour les donnée par les valeurs calculé à l'étape précédent en parcourant une deuxieme fois l'image(on recopie aussi l'entete)
	si ppm : 
		- On transforme notre image en en image en niveau de gris pour faire l'histogramme (on l'a stocke dans un fichier temporaire)
		- On recupère l'histogramme directement
		- on calcule les nouvelles valeurs
		- on met à jour les donnée par les valeurs calculé à l'étape précédent en parcourant une deuxieme fois l'image(on recopie aussi l'entete)
*/

int main(int argc, char const *argv[])
{
	if( argc < 3)return -1;
	size_t size_input = strlen(argv[1]);
	size_t size_output = strlen(argv[2]);
	if(getFileExtention(argv[1][size_input-2]) != getFileExtention(argv[2][size_output-2])){
		printf("input and output not the same extention file\n");
		return -1;
	}
	int * histogramme = (int *) calloc( INT_NUMBER, sizeof(int) );
	int * new_values = (int *) calloc( INT_NUMBER, sizeof(int) );
	if(getFileExtention(argv[1][size_input-2]) == 1){
		printf("ppm file detect\n");
		grayscaleConversion(argv[1]);
		FILE * fd= fopen(GRAYSCALE_FILENAME,"r");
		setHistogramme(fd,histogramme);
		fclose(fd);	
		remove(GRAYSCALE_FILENAME);	
	}
	else{
		printf("pgm file detect\n");
		FILE * fd = fopen(argv[1],"r");
		unsigned char ch;
		int eol_count = 0;
		while(eol_count < 3){
			ch = fgetc(fd);
			if(ch==10)eol_count++;
		}
		setHistogramme(fd,histogramme);
		fclose(fd);
	}
	FILE * fd_input = fopen(argv[1],"r");
	FILE * fd_output = fopen(argv[2],"w");
	if(fd_input == NULL || fd_output == NULL){
		printf("Cannot read the file\n");
		return -1;
	}
	unsigned char ch;
	int n;
	int eol_count = 0;
	int size_count = 2;
	int size_index_count = 0;
	int size[2] = {0,0};
	printf("Quantization number (number of integral) (between 0 and 255) : ");
	scanf("%d",&n);
	do{
		ch = fgetc(fd_input);
		/*On reprend l'entête du fichier de base*/
		if(eol_count<3)fprintf(fd_output,"%c",ch);
		/*sur la deuxième ligne du fichier on récupère la taille de l'image */
		if(eol_count==1){
			if('0' <= ch && ch <= '9'){
				switch (size_count)
				{
				case 2:
					size[size_index_count]+=(ch-'0')*100;
					size_count--;
					break;
				case 1:
					size[size_index_count]+=(ch-'0')*10;
					size_count--;
					break;
				case 0:
					size[size_index_count]+=(ch-'0');
					size_count = 2;
					break;
				
				default:
					break;
				}
			}
			else{
				size_index_count++;;
			}
			if(size_index_count>1){
				setNewValues(histogramme,new_values,size,n);
			}
		}
		/*Si on arrive à la quatrième ligne, debut des données de l'image*/
		if(eol_count >= 3){
			fprintf(fd_output,"%c",new_values[ch]);
		}
		/*Si un end of line, on incremente la variable pour savoir à quel ligne du fichier nous sommes*/
		if(ch == 10)eol_count++;
	}while(!feof(fd_input));
	fclose(fd_input);
	fclose(fd_output);
	free(histogramme);
	free(new_values);
}