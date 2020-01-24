/*
Algoritmos e Programação de Computadores - 2/2019
Aluno(a): Anderson Vieira do Nascimento
Matricula: 190102322
Turma: B
Versão do compilador: GCC 7.4.0
Descricao: Programa que implementa o algoritmo
K-vizinhos mais proximos (K-nearest neighbors).
Utiliza metodos para leitura de arquivos no
sistema.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

/*-------------------------------------------------
Type of data
-------------------------------------------------*/

/*
This structure represents the data within the docu-
-ment used on this study. It has all the attributes
defined on the website 

	https://archive.ics.uci.edu/ml/datasets/Glass+Identification

*/
typedef struct glass{

	int id;
	double refractive_index;
	double sodium;
	double magnesium;
	double aluminium;
	double silicon;
	double potassium;
	double calcium;
	double barium;
	double iron;
	int type;

}glass;

/*
This structure is necessary to the KNN algorithm.
With the information stored on the variables is pos-
-sible to count the occurrences of a given type while
using the distance calculated on the process.
*/
typedef struct similarity_factor{

	double dist;
	int type;

}similarity_factor;

/*-------------------------------------------------
File processing functions
-------------------------------------------------*/

/*
Function to load, read and extract the data from
the existing file on the filesystem. It uses type_
_mapping, write_on_file and attribute.
*/
glass * read_file(int * size);
/*
Function to return the string that is represented
by the number of the type.
*/
char * type_mapping(int type);
/*
Function to write the resulting data after the
processing made by the KNN algorithm. The data
is written according to the pattern of the file.
*/
void write_on_file(glass new_glass);
/*
Function to store the values on their correct
variables. The program does a indexation of the
parameters on the file, starting by one from the
leftmost value on a line. By writing the resulting
data on the file, it was intended to increase
more information to the next evaluation.
*/
void attribute(glass * g, char * att, int att_index);

/*-------------------------------------------------
User Interface functions
-------------------------------------------------*/

/*
Function that guides the user through the insertion
of the values on the new data.
*/
glass read_glass(int id, int glass_number);
/*
Function that guides the user through the insertion
of the parameters used on the KNN algorithm. It has
messages to inform whether a number is valid or not,
given the constraints on the document.
*/
void read_parameters(int * d, int * k);
/*
Function used to show messages to the user.
*/
void show_message(int option);

/*-------------------------------------------------
KNN Algorithm - Implementation and other functions
-------------------------------------------------*/

/*
Returns a double value representing the distance
between two variables (x and y)of the same data
type. The formula is: 

	fabs(x.att_1 - y.att_1) + fabs(x.att_2 - y.att_2);

Where att is 'attribute'.
*/
double manhattan_distance(glass x, glass y);
/*Returns a double value representing the distance
between two variables (x and y)of the same data
type. The formula is: 

	(x.att_1 - y.att_1)^2 + (x.att_2 - y.att_2)^2;

Where att is 'attribute'.
*/
double euclidean_distance(glass x, glass y);
/*
The three following functions are used to the sorting
algorithm. Using the Quicksort algorithm was the
author's choice, because it has complexity of O(Nlog N)
on the best case.

Function to exchange the values between two variables
of the same data type.
*/
void swap(similarity_factor * x, similarity_factor * y);
/*
Function to do the partition process. This function
selects a index, which is called 'pivot' and divides
the array into two parts (one part has all the elements
grater than the number on the choosen index, the other part 
has the elements less than or equal than this number.); 
*/
int partition(similarity_factor v[], int l, int r);
/*
The process made on the previous functions is repeated
recursively on this function. The algoritm uses the
divide and conquer strategy, so it has to apply the
partition process to the both sides of the array.

So the array is finally sorted.
*/
void sort(similarity_factor v[], int l, int r);
/*
This function uses all the previous functions on this
section to return the result that will be stored on
the variable to the new data.
*/
int k_nearest_neighbors(glass new_glass, glass * glasses, int size, int d, int k);

/*-------------------------------------------------
More functions
-------------------------------------------------*/

/*
Simple function to converts a string into a double
value.
*/
double str2double(char * att);

int main()
{

	int size = 0, t, glass_number = 1;
	glass * glasses = read_file(&size);
	show_message(6);
	scanf("%d", &t);
	while(glass_number <= t){
		glass new_glass = read_glass(++size, glass_number++);
		int d, k;
		read_parameters(&d, &k);
		new_glass.type = k_nearest_neighbors(new_glass, glasses, size, d, k);
		write_on_file(new_glass);		
	}

	free(glasses);
	return 0;
}

double str2double(char * att){
	int i=0, after_point = 0, frac_size = 0;
	double value = .0;
	for(i=0;i<strlen(att);i++){
		if(after_point){
			frac_size++;
		}
		if(att[i] == '.'){
			after_point = i;
		}
	}
	if(!after_point){
		int factor = 1;
		for(i=strlen(att)-1;i>=0;i--){
			value+=(att[i]-'0')*factor;
			factor*=10;
		}
	}else{
		frac_size*=(-1);
		for(i=strlen(att)-1;i>=0;i--){
			if(att[i]!='.'){
				value+=(att[i]-'0')*pow(10, frac_size++);
			}
		}
	}
	return value;
}

void attribute(glass * g, char * att, int att_index){
	double value = str2double(att);
	switch(att_index){
		case 1: g->id = value; break;
		case 2: g->refractive_index = value; break;
		case 3: g->sodium = value; break;
		case 4: g->magnesium = value; break;
		case 5: g->aluminium = value; break;
		case 6: g->silicon = value; break;
		case 7: g->potassium = value; break;
		case 8: g->calcium = value; break;
		case 9: g->barium = value; break;
		case 10: g->iron = value; break;
		case 11: g->type = value; break;
	}
}

glass * read_file(int * size){
	FILE * dataset = fopen("glass.data", "r");
	if(dataset == NULL){
		printf("File 'glass.data' doesn't exists on filesystem!\n");
		exit(EXIT_FAILURE);
	}
	glass * glasses = NULL;
	glass current_glass;
	char line[100];
	while(fscanf(dataset, "%s", line)!=EOF){
		char * att = NULL;
		int att_index = 1;
		att = strtok(line, ",");
		while(att!=NULL){
			attribute(&current_glass, att, att_index++);
			att = strtok(NULL, ",");
		}
		(*size)++;
		glass * ptr = (glass*)realloc(glasses, (*size)*sizeof(glass));
		glasses = ptr;
		glasses[(*size)-1] = current_glass;
	}
	fclose(dataset);
	return glasses;
}

double manhattan_distance(glass x, glass y){
	double dist = .0;
	dist += fabs(x.refractive_index - y.refractive_index);
	dist += fabs(x.sodium - y.sodium);
	dist += fabs(x.magnesium - y.magnesium);
	dist += fabs(x.aluminium - y.aluminium);
	dist += fabs(x.silicon - y.silicon);
	dist += fabs(x.potassium - y.potassium);
	dist += fabs(x.calcium - y.calcium);
	dist += fabs(x.barium - y.barium);
	dist += fabs(x.iron - y.iron);
	return dist;
}

double euclidean_distance(glass x, glass y){
	double dist = .0;
	dist += (x.refractive_index - y.refractive_index)*(x.refractive_index - y.refractive_index);
	dist += (x.sodium - y.sodium)*(x.sodium - y.sodium);
	dist += (x.magnesium - y.magnesium)*(x.magnesium - y.magnesium);
	dist += (x.aluminium - y.aluminium)*(x.aluminium - y.aluminium);
	dist += (x.silicon - y.silicon)*(x.silicon - y.silicon);
	dist += (x.potassium - y.potassium)*(x.potassium - y.potassium);
	dist += (x.calcium - y.calcium)*(x.calcium - y.calcium);
	dist += (x.barium - y.barium)*(x.barium - y.barium);
	dist += (x.iron - y.iron)*(x.iron - y.iron);
	return dist;
}

void show_message(int option){
	switch(option){
		case 1: 
			printf("Insert below all the fields required to register a new glass:\n\n");
		break;
		case 2: 
			printf("\nNow the program will execute the KNN algorithm to\ndetermine a type for the glass above.\n");
		break;
		case 3:
			printf("\nInsert the number that corresponds to one of the distances that can be taken:\n");
			printf("1 - Manhattan Distance;\n");
			printf("2 - Euclidean Distance;\n");
			printf("Which will be? ");
		break;
		case 4:
			printf("\nInsert the K parameter for the algorithm.\nIt must to be an odd number greater than 0\nand less than or equal to 15: ");
		break;
		case 5:
			printf("\nThe type of the glass is, by approximation, ");
		break;
		case 6:
			printf("Add glasses to the dataset\n\nHow many glasses do you want to add to the dataset? ");
		break;
	}
}

glass read_glass(int id, int glass_number){
	show_message(1);
	glass g;
	g.id = id;
	printf("\tGlass %d:\n", glass_number);
	printf("Refractive Index (RI): ");
	scanf("%lf", &g.refractive_index);
	printf("Sodium (Na): ");
	scanf("%lf", &g.sodium);
	printf("Magnesium (Mg): ");
	scanf("%lf", &g.magnesium);
	printf("Aluminium (Al): ");
	scanf("%lf", &g.aluminium);
	printf("Silicon (Si): ");
	scanf("%lf", &g.silicon);
	printf("Potassium (K): ");
	scanf("%lf", &g.potassium);
	printf("Calcium (Ca): ");
	scanf("%lf", &g.calcium);
	printf("Barium (Ba): ");
	scanf("%lf", &g.barium);
	printf("Iron (Fe): ");
	scanf("%lf", &g.iron);
	return g;
}

void read_parameters(int * d, int * k){
	show_message(2);
	int val;
	show_message(3);
	while(scanf("%d", &val) && (val < 1 || val > 2)){
		printf("\nUnknown option!\n");
		show_message(3);
	}
	*d = val;
	show_message(4);
	while(scanf("%d", &val)){
		if(val < 0){
			printf("\nK has to be positive!\n");
		}else if(val%2 == 0){
			if(val == 0){
				printf("\nK must not to be zero!\n");
			}else if(val > 15){
				printf("\nK has to be less than or equal to 15!\n");
			}else{
				printf("\nK has to be odd!\n");
			}
		}else if(val > 15){
			printf("\nK has to be less than or equal to 15!\n");
		}else{
			break;
		}
		show_message(4);
	}
	*k = val;
}

void swap(similarity_factor * x, similarity_factor * y){
	similarity_factor aux = *x;
	*x = *y;
	*y = aux;
}

int partition(similarity_factor v[], int l, int r){
	int k = l;
	int i = l;
	int pivot = r;
	while(i < r){
		if(v[i].dist <= v[pivot].dist){
			swap(&v[k], &v[i]);
			k++;
		}
		i++;
	}
	swap(&v[k], &v[pivot]);
	return k;
}

void sort(similarity_factor v[], int l, int r){
	if(l < r){
		int p = partition(v, l, r);
		sort(v, l, p-1);
		sort(v, p+1, r);
	}
}

char * type_mapping(int type){
	switch(type){
		case 1: return "building_windows_float_processed";
		case 2: return "building_windows_non_float_processed";
		case 3: return "vehicle_windows_float_processed";
		case 4: return "vehicle_windows_non_float_processed";
		case 5: return "containers";
		case 6: return "tableware";
	}
	return "headlamps";
}

void write_on_file(glass new_glass){
	FILE * dataset = fopen("glass.data", "a");
	fprintf(dataset, "%d,%.5lf,%.2lf,", new_glass.id, new_glass.refractive_index, new_glass.sodium);
	fprintf(dataset, "%.2lf,%.2lf,%.2lf,", new_glass.magnesium, new_glass.aluminium, new_glass.silicon);
	fprintf(dataset, "%.2lf,%.2lf,%.2lf,", new_glass.potassium, new_glass.calcium, new_glass.barium);
	fprintf(dataset, "%.2lf,%d\n", new_glass.iron, new_glass.type);
	fclose(dataset);
}

int k_nearest_neighbors(glass new_glass, glass * glasses, int size, int d, int k){

	similarity_factor distances[size];
	int i;
	for(i=0;i<size;i++){
		if(d == 1){
			distances[i].dist = manhattan_distance(new_glass, glasses[i]);
		}else{
			distances[i].dist = euclidean_distance(new_glass, glasses[i]);
		}
		distances[i].type = glasses[i].type;	
	}

	sort(distances, 0, size-1);
	int * counter = (int *)calloc(8, sizeof(int));
	for(i=0;i<k;i++){
		counter[distances[i].type]++;
	}
	int max_index = counter[0];
	for(i=1;i<=7;i++){
		if(counter[i] > counter[max_index]){
			max_index = i;
		}
	}
	show_message(5);
	printf("%s.\n", type_mapping(max_index));
	return max_index;
}