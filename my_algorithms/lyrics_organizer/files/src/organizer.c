#include "organizer.h"

int consistency(FILE* k, FILE* r, FILE* e, FILE* p){
	if(k == NULL || r == NULL || e == NULL || p == NULL){
		return 0;
	}
	return 1;
}

int lineCounter(FILE* arq){
	long long size;
	size_t result;

	fseek(arq, 0, SEEK_END);
	size = ftell(arq);
	rewind(arq);

	char buff[size+10];
	result = fread(buff, 1, size, arq);
	if(result!=size){
		printf("Erro de leitura!\n");
		exit(EXIT_FAILURE);
	}
	buff[size] = '\0';

	int br = 1, i;

	for(i=0;buff[i]!='\0';i++){
		if(buff[i] == '\n'){
			br++;
		}
	}

	return br;
}

char** readFile(char** matrix, FILE* arq){
	long long size;
	size_t result;

	fseek(arq, 0, SEEK_END);
	size = ftell(arq);
	rewind(arq);

	char buff[size+10];
	result = fread(buff, 1, size, arq);
	if(result!=size){
		printf("Erro de leitura!\n");
		exit(EXIT_FAILURE);
	}
	buff[size] = '\0';

	int br = 1, i;

	for(i=0;buff[i]!='\0';i++){
		if(buff[i] == '\n'){
			br++;
		}
	}

	matrix = (char**)malloc(br*sizeof(char*));
	for(i=0;i<br;i++){
		matrix[i] = (char*)malloc((300)*sizeof(char));
	}

	char line[300];
	int index=0, indexm=0;

	for(i=0;buff[i]!='\0';i++){
		if(buff[i]=='\n'){
			line[index] = '\0';
			strcpy(matrix[indexm++], line);
			index = 0;
		}else if(buff[i+1] == '\0'){
			line[index++] = buff[i];
			line[index] = '\0';
			strcpy(matrix[indexm++], line);
		}else{
			line[index++] = buff[i];
		}
	}

	return matrix;

}
