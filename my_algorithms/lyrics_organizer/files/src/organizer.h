#ifndef ORGANIZER_H_ORGANIZER
#define ORGANIZER_H_ORGANIZER

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Verifica se os arquivos foram abertos
int consistency(FILE* k, FILE* r, FILE* e, FILE* p);

//Conta a quantidade de linhas dos arquivos
int lineCounter(FILE* arq);

//Realiza a leitura dos arquivos
char** readFile(char** matrix, FILE* arq);

#endif
