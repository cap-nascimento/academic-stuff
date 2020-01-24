#include <stdio.h>

int main(){

	int i, j;
	for(i=10;i>=1;i--){
		printf("Maaaariana conta %d, mariana conta %d!\n", i, i);
		for(j=1;j<=i;j++){
			printf("é %d, ", j);
		}
		printf("é.\nAna, viva a mariana, viva a marianaaa...\n\n");
	}

	return 0;
}