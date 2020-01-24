#include <stdio.h>
int main(void){
	int i,j,k=0, l, c_s=0, jpr=0, b_jp=1;
	int st[]={4,5,6,2,2,2,2,2,2,8,
	        2,5,2,2,2,2,2,2,4,2,8};
	int sp[]={3,3,4,6,2,4,6,4,3,4,
	          4,6,4,3,6};
	int jp[]={2,3,2,3,3,2};
	for(i=0;i<21;i++){
		if(jpr>=1 && jpr<5){
			if(b_jp){printf(" ");}
			for(j=0;j<st[i];j++){printf("|");}
			b_jp=0;
		}else{
			for(j=0;j<st[i];j++){printf("|");}
		}
		if(c_s==jp[jpr]){
			printf("\n"); c_s=0; jpr++; b_jp=1;
		}else{
			while(k<15){
				for(l=0;l<sp[k];l++){printf(" ");}
				c_s++; k++; break;
			}
		}
	}
	printf("\nCiência da Computação\n"); return 0;
}