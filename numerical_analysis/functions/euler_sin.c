#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define M_E 1.41

unsigned long long fac(int x){
	if(x == 1){
		return 1;
	}else{
		return x*fac(x-1);
	}
}

double sinfn(double x){

	int i;
	int odd[8] = {1, 3, 5, 7, 9, 11, 13, 15};
	unsigned long long factorial[8];

	for(i=0;i<8;i++){
		factorial[i] = fac(odd[i]);
	}

	double result = 0.0;
	for(i=0;i<8;i++){
		if(i%2 == 0){
			result+= (double)(pow(x, odd[i]))/factorial[i];
		}else{
			result-= (double)(pow(x, odd[i]))/factorial[i];
		}
	}

	return result;

}

double eulerSin(int x){

	if(x > 709){
		printf("Size Limit!\n");
		return 0.0;
	}
	return pow(M_E, x) - sinfn(x);

}

int main(void){
	
	double *sequence = NULL; int c=1;

	int i, n;
	scanf("%d", &n);

	for(i=0;i<=n;i++){
		double fx = eulerSin(i);
		if(fx == 0.0){
			break;
		}else{

			sequence = (double*)realloc(sequence, c*sizeof(double));
			sequence[c-1] = fx;
			c++;

		}
	}
	c--;	
	int j;
	i = 0;
	for(j=0;j<c;j++){
		printf("f(%d) = %.4lf\n", i, sequence[j]);
		i++;
	}

	free(sequence);

	return 0;
}