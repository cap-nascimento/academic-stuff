#include "../files/src/organizer.h"

int main(int argc, char* argv[]){

	//Leitura dos arquivos
	FILE *kanji, *romaji, *english, *portuguese, *lyrics;
	kanji = fopen("../files/kanji.txt", "rb");
	romaji = fopen("../files/romaji.txt", "rb");
	english = fopen("../files/english.txt", "rb");
	portuguese = fopen("../files/portuguese.txt", "rb");

	//Criação do arquivo de saída
	lyrics = fopen("../files/lyrics.txt", "wb");

	if(!consistency(kanji, romaji, english, portuguese)){
		printf("Erro de leitura!\n");
		exit(EXIT_FAILURE);
	}

	//Linhas dos arquivos
	int lkj = lineCounter(kanji);
	int lrj = lineCounter(romaji);
	int len = lineCounter(english);
	int lpo = lineCounter(portuguese);

	if(lkj == lrj && lkj == len && lkj == lpo){
		printf("Gerando o arquivo...\n");
	}else{
		printf("Revise a disposição dos arquivos!\n");
		exit(EXIT_FAILURE);
	}

	//Matrizes de strings
	char** kj = NULL;
	char** rj = NULL;
	char** en = NULL;
	char** po = NULL;

	kj = readFile(kj, kanji);
	rj = readFile(rj, romaji);
	en = readFile(en, english);
	po = readFile(po, portuguese);
	
	int i;
	for(i=0;i<lkj;i++){
		if(strlen(kj[i]) == 0 || 
		  (strcmp(kj[i], rj[i]) == 0 && strcmp(kj[i], en[i]) == 0)){
			continue;
		}else if(i!=lkj-1 && strlen(kj[i+1])==0){
			fprintf(lyrics, "%s\n", kj[i]);
			fprintf(lyrics, "%s\n", rj[i]);
			fprintf(lyrics, "%s\n", en[i]);
			fprintf(lyrics, "%s\n\n", po[i]);
		}else{
			fprintf(lyrics, "%s\n", kj[i]);
			fprintf(lyrics, "%s\n", rj[i]);
			fprintf(lyrics, "%s\n", en[i]);
			fprintf(lyrics, "%s\n", po[i]);
		}
	}

	free(kj);
	free(rj);
	free(en);
	free(po);

	fclose(kanji);
	fclose(romaji);
	fclose(english);
	fclose(portuguese);
	fclose(lyrics);
	printf("Arquivo gerado com sucesso!\n");

	return 0;
}
