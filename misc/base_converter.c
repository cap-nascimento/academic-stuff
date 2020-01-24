/*
Algoritmos e Programação de Computadores - 2/2019
Aluno(a): Anderson Vieira do Nascimento
Matricula: 19/0102322
Turma: B
Versão do compilador: gcc 7.4.0
Descricao:
	Programa para conversao de numero em uma base especificada para
	a base decimal. O numero e representado por uma string composta
	pelo numero e pela base (octal, decimal ou hexadecimal) separados
	por um underscore '_'.
*/

/*
	Compilacao: gcc -Wall 190102322_AndersonNascimento_projeto1.c -lm
	Execucao: ./a.out
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

/*O programa utiliza mnemonicos para TRUE e FALSE*/
#define TRUE 1
#define FALSE 0

/*
	Funcao que separa a parte da string
	que representa a base a ser considerada.
	Primeiro verifica-se a existencia de uma
	substring apos o caractere '_', depois 
	e feita uma verificacao se a substring
	e composta apenas por numeros. 
	Retorna TRUE se atende aos requisitos
	mencionados acima e FALSE se contrario. 
*/
int validate_base_input(char * str);

/*
	Funcao que separa a parte da string
	que representa o numero a ser convertido.
	Apos obter a substring do numero e verificar
	o seu tamanho (se for igual 0, a substring e
	invalida), e feita uma verificacao dos carac-
	-teres que compoem a string em relacao a base
	considerada. Lembrando que antes dessa funcao
	ser chamada, e feita uma verificacao da base
	(se é 2, 8 ou 16). Para verificar se o numero
	tem parte fracionaria, o ponteiro para inteiro
	recebe valor 1 se for encontrado uma virgula
	na substring analisada.
	Retorna TRUE se atende aos requisitos
	mencionados acima e FALSE se contrario. 
*/
int validate_number_input(char * str, char * number, int * frac, int base);

/*
	Funcao que retorna o valor decimal
	que o caractere representa, dadas
	as funcionalidades do programa.
*/
int value_mapping(char c);


/*
	Funcao que realiza a conversao do numero
	de acordo com o somatorio especificado
	para a conversao de bases. E feito um tratamento
	caso haja parte fracionaria no numero: primeiro
	conta-se quantos caracteres existem apos a virgula
	e atribui-se o valor negativado ao expoente.
	O laco de repeticao que acumula a soma na variavel
	que representa o valor convertido e executado da
	mesma forma, com a excecao de que existe um caractere
	',' na string do numero.
	Retorna um valor real que representa o numero convertido.
*/
double convert_to_decimal(char * number, int base, int frac);

/*
	Recebe o ponteiro da string validada
	em validate_base_input() e realiza a
	conversao de string para inteiro, atribuindo
	o valor obtido no ponteiro para inteiro
	da base.
*/
void extract_base(char * str, int * base);

/*
	Funcao responsavel por interagir com o usuario
	em relacao as entradas que o mesmo fornece.
	Tem caracteristica recursiva e o caso base e 
	atingido quando os requisitos exigidos
	por validate_base_input() e validade_number_input()
	sao atendidos.
*/
void insert_data(char * str, char * number, int * base, int * frac);

/*
	Mensagem exibida no inicio da execucao do programa
*/
void presentation_end();

/*
	Mensagem exibida apos a execucao de uma conversao.
*/
void presentation_start();

/*
	Mensagem exibida quando o usuario insere uma
	opcao invalida.
*/
void presentation_error();

/*
	Mensagem exibida quando o usuario e solicitado
	a inserir o numero e a base.
*/
void insert_data_message();

/*

	Funcao principal. E responsavel pela
	interacao com o usuario ao chamar as
	funcoes que exibem mensagens e solicitam
	a entrada do usuario, alem da chamada
	da funcao que realiza a conversao.

*/
int main()
{

	presentation_start();
	int option;
	while(scanf("%d", &option) && option-2){
		getchar();
		if(option != 1){
			presentation_error();
			continue;
		}
		printf("\n");
		char input[100];
		char number[100];
		int base, frac = 0;
		insert_data(input, number, &base, &frac);
		printf("\n\t\tInput: %s on base %d\n", number, base);
		printf("\t\tOutput: %lf\n\n", convert_to_decimal(number, base, frac));

		presentation_end();
	}
	printf("\n\t\tBye :)\n\n");

	return 0;
}

void presentation_start(){
	printf("Hi! This is the base converter (binary, octal, hexadecimal) to decimal.\n");
	printf("Options:\n1 - Convert;\n2 - Exit.\nWhat you want to do? ");
}

void presentation_end(){
	printf("\nHello again!\n");
	printf("Options:\n1 - Convert;\n2 - Exit.\nWhat you want to do? ");
}

void presentation_error(){
	printf("\n\t\tThat option does not exists!\n\n");
	printf("Options:\n1 - Convert;\n2 - Exit.\nWhat you want to do? ");	
}

int validate_number_input(char * str, char * number, int * frac, int base){
	int i=0, qtd_comma = 0, position_comma = 0;
	for(;str[i]!='_';i++){
		number[i] = str[i];
		if(number[i] >= 'a' && number[i] <= 'z'){
			number[i] -= 32;
		}
	}
	number[i] = '\0';
	if(strlen(number) == 0){
		return FALSE;
	}
	if(base == 2){
		for(i=0;number[i]!='\0';i++){
			if(number[i] >= '0' && number[i] <= '1' ){
				continue;
			}else{
				if(number[i] == ','){
					*frac = 1;
					qtd_comma++;
					position_comma = i;
					continue;
				}
				return FALSE;
			}
		}
	}else if(base == 8){
		for(i=0;number[i]!='\0';i++){
			if(number[i] >= '0' && number[i] <= '7' ){
				continue;
			}else{
				if(number[i] == ','){
					*frac = 1;
					qtd_comma++;
					position_comma = i;
					continue;
				}
				return FALSE;
			}
		}
	}else if(base == 16){
		for(i=0;number[i]!='\0';i++){
			if((number[i] >= '0' && number[i] <= '9') ||
				(number[i]>='A' && number[i] <= 'F')){
				continue;
			}else{
				if(number[i] == ','){
					*frac = 1;
					qtd_comma++;
					position_comma = i;
					continue;
				}
				return FALSE;
			}
		}
	}
	if(qtd_comma == 0 || qtd_comma == 1){
		if(qtd_comma == 1 && position_comma == 0){
			return FALSE;
		}
		return TRUE;
	}
	return FALSE;
}

int validate_base_input(char * str){
	int i, tam = strlen(str), index=0;
	char base[30];
	for(i=0;str[i]!='\0';i++){
		if(str[i] == '_'){
			i++;
			break;
		}
	}
	if(i == tam){
		return FALSE;
	}
	while(i < tam){
		base[index++]=str[i++];
	}
	base[index] = '\0';
	for(i=0;base[i]!='\0';i++){
		if(base[i] < '0' || base[i] > '9'){
			return FALSE;
		}
	}
	return TRUE;
}

void extract_base(char * str, int * base){
	int i = strlen(str)-1;
	int s = 0, d=1;
	while(str[i]!='_'){
		s+=(str[i]-'0')*d;
		d*=10;
		i--;
	}
	*base = s;
}

void insert_data_message(){	
	printf("Insert the number with the following model:\n");
	printf("\n\t\t[number]_[base] (Ignore the brackets)\n\nInput: ");
}

void insert_data(char * str, char * number, int * base, int * frac){
	insert_data_message();
	scanf("%[^\n]%*c", str);
	if(validate_base_input(str)){
		extract_base(str, base);
		if(*base == 2 || *base == 8 || *base == 16){
			if(validate_number_input(str, number, frac, *base)){
				return;
			}else{
				printf("\n\t\tIncorrect input on number!\n\n");
				insert_data(str, number, base, frac);
			}
		}else{
			printf("\n\t\tSorry, we do not deal with this base!\n\n");
			insert_data(str, number, base, frac);
		}
	}else{
		printf("\n\t\tIncorrect format!\n\n");
		insert_data(str, number, base, frac);
	}
}

int value_mapping(char c){
	if(c >='0' && c <='9'){
		return c-'0';
	}
	return c-'7';
}

double convert_to_decimal(char * number, int base, int frac){
	double answer = 0;
	int i, exp=0;
	if(!frac){
		for(i=strlen(number)-1;i>=0;i--){
			answer += (value_mapping(number[i]))*pow(base, exp++);
		}
	}else{
		int beyond_comma = 0;
		for(i=strlen(number)-1;number[i]!=',';i--){
			beyond_comma++;
		}
		exp = beyond_comma*(-1);
		for(i=strlen(number)-1;i>=0;i--){
			if(number[i] == ','){
				continue;
			}else{
				answer += (value_mapping(number[i]))*pow(base, exp++);
			}
		}
	}
	return answer;
}
