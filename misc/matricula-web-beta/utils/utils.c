#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "utils.h"
#include "../binary_search_tree/bst.h"
#include "../doubly_linked_list/dlist.h"

FILE * get_file(char * filename){
    FILE * file = fopen(filename, "rb");
    if(file == NULL){
        printf("File reading error!\n");
        printf("Exiting\n\n");
        exit(EXIT_FAILURE);
    }
    return file;
}

int verify_file(int argc, char * argv[]){
    
    // Verify the number of arguments passed by command line
    if(argc != 2){
        printf("Expected 1 argument!\n");
        printf("Exiting\n\n");
        return 0;
    }

    // Verify the consistency of the parameter
    char * ptr = strtok(argv[1], ".");
    char name_extension[2][100];
    int index = 0, i;
    while(ptr != NULL){
        if(index >= 2){
            printf("Invalid filename!\n");
            printf("Exiting\n");
            return 0;
        }else{
            strcpy(name_extension[index++], ptr);
            ptr = strtok(NULL, ".");
        }
    }
    if(index != 2){
        printf("Invalid filename!\n");
        printf("Exiting\n");
        return 0;
    }

    // verify format of the file
    for(i=0;i<strlen(name_extension[1]);i++){
        name_extension[1][i] = tolower(name_extension[1][i]);
    }
    if(strcmp(name_extension[1], "txt") != 0){
        printf("Invalid format (only .txt allowed)!\n");
        printf("Exiting\n");
        return 0;
    }

    return 1;
}

void greetings(){
    printf("\t\t ******** Matricula Web Beta ********\n");
    printf("\t\t *Welcome to the matricula web beta!*\n");
    printf("\t\t *Please wait while we check the gi-*\n");
    printf("\t\t *-ven information :)               *\n");
    printf("\t\t ************************************\n\n");
}

char * read_file(FILE * arq){
    long lSize;
    char * buffer;
    size_t result;

    fseek(arq, 0, SEEK_END);
    lSize = ftell(arq);
    rewind(arq);

    buffer = (char*)malloc(sizeof(char)*lSize);
    if(buffer == NULL){
        printf("Memory allocation error!\n");
        printf("Exiting\n\n");
        exit(EXIT_FAILURE);
    }

    result = fread(buffer, 1, lSize, arq);
    if(result != lSize){
        printf("File reading error!\n");
        printf("Exiting\n\n");
        exit(EXIT_FAILURE);
    }

    fclose(arq);
    return buffer;
}

int strtoint(char * string){
    int number = 0, f = 1, i;
    for(i=strlen(string)-1;i>=0;i--){
        number += (string[i]-'0')*f;
        f*=10;
    }
    return number;
}

double strtodouble(char * string){
    double number = .0;
    int size = 0, i;
    for(i = strlen(string)-1;string[i]!='.';i--) size++;
    size *= (-1);
    for(i = strlen(string)-1;i>=0;i--){
        if(string[i] == '.')continue;
        number += (string[i]-'0')*pow(10, size);
        size++;
    }

    return number;
}

char * student_rating_calculator(double grade){
    if(grade <= 10.00){
        if(grade >= 9.00){
            return "SS";
        }else{
            if(grade >= 7.00){
                return "MS";
            }else{
                if(grade >= 5.00){
                    return "MM";
                }else{
                    if(grade >= 3.00){
                        return "MI";
                    }else{
                        if(grade >= 1.00){
                            return "II";
                        }
                    }
                }
            }
        }
    }
    return "SR";
}

char * format_string(double percent, int qtd){
    if(percent == 0){
        return "0.00(0)";
    }
    char * str = (char*)malloc(100*sizeof(char));
    int index = 0;
    int trunc = percent*100;
    char str_double[10], str_int[10];
    while(trunc > 0){
        str_double[index++] = (trunc%10)+'0';
        trunc/=10;
    }
    str_double[index] = '\0';
    index = 0;
    while(qtd > 0){
        str_int[index++] = (qtd%10)+'0';
        qtd/=10;
    }
    str_int[index] = '\0';
    int i;
    index = 0;
    for(i=strlen(str_double)-1;i>=0;i--){
        if(i == 1){
            str[index++] = '.';
            str[index++] = str_double[i];
        }else{
            str[index++] = str_double[i];   
        }
    }
    str[index++] = '(';
    for(i=strlen(str_int)-1;i>=0;i--){
        str[index++] = str_int[i];
    }
    str[index++] = ')';
    str[index] = '\0';
    //printf("%s\n", str);
    return str;
}