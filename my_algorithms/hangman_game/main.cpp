#include <bits/stdc++.h>
using namespace std;

bool head, trunk, left_arm, right_arm, right_leg, left_leg;
bool won = false;
string secret;
char parts[6][100] = {"bodyparts/head.txt", "bodyparts/trunk.txt", 
						"bodyparts/left_arm.txt", "bodyparts/right_arm.txt", 
						"bodyparts/left_leg.txt", "bodyparts/right_leg.txt"};
set<char> already;

void init_mecanism(){
	head = trunk = left_arm = right_arm = right_leg = left_leg = false;
}

void open_file(int index){
FILE * pFile;
  long lSize;
  char * buffer;
  long result;

  pFile = fopen ( parts[index] , "rb" );
  if (pFile==NULL) {fputs ("File error",stderr); exit (1);}

  // obtain file size:
  fseek (pFile , 0 , SEEK_END);
  lSize = ftell (pFile);
  rewind (pFile);

  // allocate memory to contain the whole file:
  buffer = (char*) malloc (sizeof(char)*lSize);
  if (buffer == NULL) {fputs ("Memory error",stderr); exit (2);}

  // copy the file into the buffer:
  result = fread (buffer,1,lSize,pFile);
  if (result != lSize) {fputs ("Reading error",stderr); exit (3);}

  /* the whole file is now loaded in the memory buffer. */
  printf("%s\n", buffer);

  // terminate
  fclose (pFile);
  free (buffer);
}

void reveal_head(){
	open_file(0);
}

void reveal_trunk(){
	open_file(1);
}

void reveal_left_arm(){
	open_file(2);
}

void reveal_right_arm(){
	open_file(3);
}

void reveal_left_leg(){
	open_file(4);
}

void reveal_right_leg(){
	open_file(5);
}

void init_game(string str){
	printf("************ JOGO DA FORCA - EJA Edition ************\n");
	init_mecanism();
	secret = "";
	for(size_t i=0;i<str.size();i++){
		if(str[i] == ' '){
			secret.push_back(' ');
		}else{
			secret.push_back('.');
		}
	}
}

void show_hint(string str, size_t s){
	printf("Dica: ");
	for(size_t i=0;i<str.size();i++){
		printf(" %c ", str[i]);
	}
	printf("(%ld letras)\n", s);
}

void print_already_used(){
	set<char>::iterator it;
	printf("Letras tentadas: ");
	for(it=already.begin();it!=already.end();it++){
		cout << *(it) << " ";
	}
	cout << endl;
	printf("\n");
}

void print_secret(){
	printf("\n");
	for(size_t i=0;i<secret.size();i++){
		printf(" %c ", secret[i]);
	}
	printf("\n");
	printf("\n");	
}

void reaveal_some(){
	printf(" E R R O U! \n");
	if(!head){
		head = true;
		reveal_head();
		print_secret();
		return;
	}
	if(!trunk){
		trunk = true;
		reveal_trunk();
		print_secret();
		return;
	}
	if(!left_arm){
		left_arm = true;
		reveal_left_arm();
		print_secret();
		return;
	}
	if(!right_arm){
		right_arm = true;
		reveal_right_arm();
		print_secret();
		return;
	}
	if(!left_leg){
		left_leg = true;
		reveal_left_leg();
		print_secret();
		return;
	}
	if(!right_leg){
		right_leg = true;
		reveal_right_leg();
		print_secret();
		return;
	}
}

bool man_completed(){
	if(head && trunk && left_arm && right_arm && left_leg && right_leg){
		return true;
	}
	return false;
}

void loser_message(){
	printf(" P E R D E U \n");
}

void show_partial_word(string s, char guess){
	for(size_t i=0;i<s.size();i++){
		if(guess == s[i]){
			secret[i] = guess;
		}
	}
	print_secret();
}

bool word_completed(){
	size_t i;
	for(i=0;i<secret.size();i++){
		if(secret[i] == '.'){
			break;
		}
	}
	if(i == secret.size()){
		return true;
	}
	return false;
}

void winner_message(){
	printf("G A N H O U \n");
}

void already_message(){
	printf("\nVOCÊ JÁ TENTOU ESSA LETRA!\n\n");
	print_already_used();
}

bool evaluation(string s, size_t j, char guess){

	if(j == s.size()){
		reaveal_some();
		if(man_completed()){
			loser_message();
			return true;
		}
	}else{
		show_partial_word(s, guess);
		if(word_completed()){
			winner_message();
			won = true;
			return true;
		}
	}
	return false;
}

int main()
{

	vector<string> words = {"lain"};
	vector<string> hints = {"anime"};
	string s;
	for(size_t i=0;i<words.size();i++){
		init_game(words[i]);
		show_hint(hints[i], words[i].size());
		char guess;
		already.clear();
		bool stop = false;
		printf("Bota a letra aq: ");
		while(cin >> guess && !stop){
			size_t j;
			for(j=0;j<words[i].size();j++){
				if(words[i][j] == guess){
					break;
				}
			}
			if(already.empty()){
				already.insert(guess);
				stop = evaluation(words[i], j, guess);
			}else{
				set<char>::iterator it = already.find(guess);
				if(it == already.end()){
					stop = evaluation(words[i], j, guess);
					already.insert(guess);
				}else{
					already_message();
				}
			}
			if(!stop){
				print_already_used();
				show_hint(hints[i], words[i].size());
				printf("Bota a letra aq: ");
			}else{
				if(!won){
					cout << "RESPOSTA: " << words[i] << endl;
				}
				break;
			}
		}
	}

	return 0;
}