#include<stdio.h>
#include<string.h>
#include<stdlib.h>

struct rgb_s {
    int r;
    int g;
    int b;
};

/*
* trouve la couleur la plus proche (canal 2 bit)
*/
int findNearestColour(int old){
    if(old < 128)return 0;
    else return 255;
}

struct rgb_s findNearestRGBColour(struct rgb_s old){
    struct rgb_s new;
    new.r = findNearestColour(old.r);
    new.g = findNearestColour(old.g);
    new.b = findNearestColour(old.b);
    return new;
}

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

void change_values(unsigned char * data, int file_extention, int size[2]){
    
    int nb_coulour;
    int nb_error;
    int index;
    struct rgb_s rgb_coulour;
    struct rgb_s rgb_error;
    
    if(file_extention == 1){
       for(int y=0;y < size[1];y++){
            for(int x=0;x<size[0]*3-1;x+=3){
                /*Si ligne impaire, alors on va de droite à gauche*/
                if(y%2){
                    index = y*size[0]*3+size[0]*3 - 3 - x;
                    //printf("%d ",index);
                    rgb_coulour.r = data[index];
                    rgb_coulour.g = data[index+1];
                    rgb_coulour.b = data[index+2];
                    rgb_coulour = findNearestRGBColour(rgb_coulour);
                    rgb_error.r = data[index]-rgb_coulour.r;
                    rgb_error.g = data[index+1]-rgb_coulour.g;
                    rgb_error.b = data[index+2]-rgb_coulour.b;
                    data[index] = rgb_coulour.r;
                    data[index+1] = rgb_coulour.g;
                    data[index+2] = rgb_coulour.b;
                    /*Application de la dipersion d"erreur*/
                    if(x!=0 && y!=size[1]-1){
                        data[index-3]           = data[index-3]             + rgb_error.r*(7.0/16.0);
                        data[index-2]           = data[index-2]             + rgb_error.g*(7.0/16.0);
                        data[index-1]           = data[index-1]             + rgb_error.b*(7.0/16.0);

                        data[index-3+size[0]*3] = data[index-3+size[0]*3]   + rgb_error.r*(1.0/16.0);
                        data[index-2+size[0]*3] = data[index-2+size[0]*3]   + rgb_error.g*(1.0/16.0);
                        data[index-1+size[0]*3] = data[index-1+size[0]*3]   + rgb_error.b*(1.0/16.0);

                        data[index+size[0]*3]   = data[index+size[0]*3]     + rgb_error.r*(5.0/16.0);
                        data[index+1+size[0]*3] = data[index+1+size[0]*3]   + rgb_error.g*(5.0/16.0);
                        data[index+2+size[0]*3] = data[index+2+size[0]*3]   + rgb_error.b*(5.0/16.0);

                        data[index+3+size[0]*3] = data[index+3+size[0]*3]   + rgb_error.r*(3.0/16.0);
                        data[index+4+size[0]*3] = data[index+4+size[0]*3]   + rgb_error.g*(3.0/16.0);
                        data[index+5+size[0]*3] = data[index+5+size[0]*3]   + rgb_error.b*(3.0/16.0);
                    }
                    if(x!=0 && y==size[1]-1){
                        data[index+3]           = data[index+3]             + rgb_error.r*(7.0/16.0);
                        data[index+4]           = data[index+4]             + rgb_error.g*(7.0/16.0);
                        data[index+5]           = data[index+5]             + rgb_error.b*(7.0/16.0);
                    }
                }
                /*Si ligne paire, alors on va de gauche à droite*/
                else{
                    index = x+y*size[0]*3;
                    //printf("%d ",index);
                    rgb_coulour.r = data[index];
                    rgb_coulour.g = data[index+1];
                    rgb_coulour.b = data[index+2];
                    rgb_coulour = findNearestRGBColour(rgb_coulour);
                    rgb_error.r = data[index]-rgb_coulour.r;
                    rgb_error.g = data[index+1]-rgb_coulour.g;
                    rgb_error.b = data[index+2]-rgb_coulour.b;
                    data[index] = rgb_coulour.r;
                    data[index+1] = rgb_coulour.g;
                    data[index+2] = rgb_coulour.b;
                    if(x!=size[0]*3-3 && y!=size[1]-1){
                        data[index+3]           = data[index+3]             + rgb_error.r*(7.0/16.0);
                        data[index+4]           = data[index+4]             + rgb_error.g*(7.0/16.0);
                        data[index+5]           = data[index+5]             + rgb_error.b*(7.0/16.0);

                        data[index+3+size[0]*3] = data[index+3+size[0]*3]   + rgb_error.r*(1.0/16.0);
                        data[index+4+size[0]*3] = data[index+4+size[0]*3]   + rgb_error.g*(1.0/16.0);
                        data[index+5+size[0]*3] = data[index+5+size[0]*3]   + rgb_error.b*(1.0/16.0);

                        data[index+size[0]*3]   = data[index+size[0]*3]     + rgb_error.r*(5.0/16.0);
                        data[index+1+size[0]*3] = data[index+1+size[0]*3]   + rgb_error.g*(5.0/16.0);
                        data[index+2+size[0]*3] = data[index+2+size[0]*3]   + rgb_error.b*(5.0/16.0);

                        data[index-3+size[0]*3] = data[index-3+size[0]*3]   + rgb_error.r*(3.0/16.0);
                        data[index-2+size[0]*3] = data[index-2+size[0]*3]   + rgb_error.g*(3.0/16.0);
                        data[index-1+size[0]*3] = data[index-1+size[0]*3]   + rgb_error.b*(3.0/16.0);
                    }
                    if(x!=size[0]*3-3 && y==size[1]-1){
                        data[index+3]           = data[index+3]             + rgb_error.r*(7.0/16.0);
                        data[index+4]           = data[index+4]             + rgb_error.g*(7.0/16.0);
                        data[index+5]           = data[index+5]             + rgb_error.b*(7.0/16.0);
                    }
                }
            }
        }
    }
    else if(file_extention == 2){
        for(int y=0;y < size[1];y++){
            for(int x=0;x<size[0];x++){
                /*Si ligne impaire, alors on va de droite à gauche*/
                if(y%2){
                    index = y*size[0]+size[0]-1 - x;
                    nb_coulour = findNearestColour(data[index]);
                    nb_error = data[index]-nb_coulour;
                    data[index] = nb_coulour;
                    /*Application de la dipersion d"erreur*/
                    if(x!=size[0]-1 && y!=size[1]-1){
                        data[index+size[0]] = data[index+size[0]] + nb_error*(5.0/16.0);
                        data[index+1+size[0]] = data[index+1+size[0]] + nb_error*(3.0/16.0);
                        data[index-1] = data[index-1] + nb_error*(7.0/16.0);
                        data[index-1+size[0]] = data[index-1+size[0]] + nb_error*(1.0/16.0);
                    }
                    if(x!=size[0]-1 && y==size[1]-1){
                        data[index+1] = data[index+1] + nb_error*(7.0/16.0);
                    }
                }
                /*Si ligne impaire, alors on va de gauche à droite*/
                else{
                    index = x+y*size[0];
                    nb_coulour = findNearestColour(data[index]);
                    nb_error = data[index]-nb_coulour;
                    data[index] = nb_coulour;
                    if(x!=size[0]-1 && y!=size[1]-1){
                        data[index+size[0]] = data[index+size[0]] + nb_error*(5.0/16.0);
                        data[index-1+size[0]] = data[index-1+size[0]] + nb_error*(3.0/16.0);
                        data[index+1] = data[index+1] + nb_error*(7.0/16.0);
                        data[index+1+size[0]] = data[index+1+size[0]] + nb_error*(1.0/16.0);
                    }
                    if(x!=0 && y==size[1]-1){
                        data[index+1] = data[index+1] + nb_error*(7.0/16.0);
                    }
                }
            }
        }
    }
}

int main(int argc, char const *argv[]){
    if( argc < 3)return -1;
	size_t size_input = strlen(argv[1]);
	size_t size_output = strlen(argv[2]);
	if(getFileExtention(argv[1][size_input-2]) != getFileExtention(argv[2][size_output-2])){
		printf("input and output not the same extention file\n");
		return -1;
	}
    FILE * fd_input = fopen(argv[1],"r");
	FILE * fd_output = fopen(argv[2],"w");
	if(fd_input == NULL || fd_output == NULL){
		printf("Cannot read the file\n");
		return -1;
	}
    int allocation_flag=0;
    int eol_count = 0;
    int size_count = 2;
	int size_index_count = 0;
	int size[2] = {0,0};
    unsigned char * data;
    int index = 0;
    unsigned char ch;
    int mul = 1;
    /*1 : ppm, 2:pgm*/
    int file_extention = 0;
    do{
        ch = fgetc(fd_input);
        switch(eol_count){
            /*Premiere ligne (type of file)*/
            case 0:
                fprintf(fd_output,"%c",ch);
                if(ch == '5'){
                    file_extention = 2;
                }
                else if(ch == '6'){
                    file_extention = 1;
                    mul=3;
                }
                break;
            /*Deuxieme ligne (size of image)*/
            case 1:
                fprintf(fd_output,"%c",ch);
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
				    size_index_count++;
			    }
                break;
            /*Troisieme ligne (max_value)*/
            case 2:
                fprintf(fd_output,"%c",ch);
                break;
            /*Quatrieme et +  : ligne (data)*/
            default:
                if(allocation_flag== 0 && file_extention == 1){
                    data = (unsigned char *) malloc( (size[0]*size[1]*3+1)*sizeof(unsigned char) );
                    allocation_flag = 1;
                }
                else if(allocation_flag== 0 && file_extention == 2){
                    data = (unsigned char *) malloc( (size[0]*size[1]+1)*sizeof(unsigned char) );
                    allocation_flag = 1;
                }
                data[index] = ch;
                index++;
                break;
        }
        if(ch == 10)eol_count++;
    }while(!feof(fd_input));
    printf("file extention : %d\n",file_extention);
    printf("size %d x %d\n",size[0],size[1]);
    change_values(data,file_extention,size);
    for(index=0;index<size[0]*size[1]*mul;index++){
        //printf("%d ",index);
        fprintf(fd_output,"%c",data[index]);
    }
    free(data);
    fclose(fd_input);
	fclose(fd_output);
}
