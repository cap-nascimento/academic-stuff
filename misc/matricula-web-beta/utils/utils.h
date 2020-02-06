#ifndef UTILS_H_INCLUDED
#define UTILS_H_INCLUDED
#include <stdio.h>
#define TRUE 1
#define FALSE 0

//function to get a pointer to the file
FILE * get_file(char * filename);
//function to verify the consistency of the given argument
int verify_file(int argc, char * argv[]);
//simple text to show when the program starts
void greetings();
//function to return a string with the file content
char * read_file(FILE * arq);
//function to convert string into integer
int strtoint(char * string);
//function to convert string to double
double strtodouble(char * string);
//function to determine student rating
char * student_rating_calculator(double grade);
//funtion to format a percent of the dataset
char * format_string(double percent, int qtd);
#endif