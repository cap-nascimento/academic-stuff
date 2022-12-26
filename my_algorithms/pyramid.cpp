#include <bits/stdc++.h>
using namespace std;

class SpotifySong{
	public:
		int bpm;
		string link;

		void print_song(){
			cout << "Link: " << link << " " 
				<< "BPM: " << bpm << endl;
		}

		bool operator<(const SpotifySong & rhc) {
			return this->bpm < rhc.bpm;
		}
};

bool is_numeric(string str){
	if(str.size() == 0) return false;
	for(char c : str){
		if(c < '0' || c > '9') return false;
	}
	return true;
}

string remove_whitespace(string str){
	string result = "";
	for(char c : str){
		if((c >= '0' && c <= '9') || (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
			result.push_back(c);
	}
	return result;
}

vector<SpotifySong> parse_songs(vector<string>&file_content){
	vector<SpotifySong> result;
	for(size_t i=1;i<file_content.size();i++){
		string line = file_content[i];
		stringstream iss(line);
		string content;
		int counter = 0;
		SpotifySong song;
		while(getline(iss, content, ',')){
			if(counter == 0)
				song.link = content;
			if(counter == 1){
				content = remove_whitespace(content);
				if(is_numeric(content))
					song.bpm = stoi(content);
				else
					song.bpm = -1;
			}
			counter++;
		}
		if(counter == 1) song.bpm = -1;
		result.push_back(song);
	}
	return result;
}

void pyramid_sort(vector<SpotifySong>&arr) {
	sort(arr.begin(), arr.end());
	vector<SpotifySong> temp(arr.size());
	size_t i = 0, j = 0;
	while(j < arr.size()){
		temp[i] = arr[j++];
		if(j == arr.size()) break;
		temp[temp.size()-i-1] = arr[j++];
		i++;
	}
	arr = temp;
}

int main(int argc, char * argv[]){

	if(argc != 2){
		cout << "You need to provide a valid filename!\n";
		exit(1);
	}

	ifstream file(argv[1]);
	vector<string> file_content;
	if(file.is_open()){
		string line;
		while(getline(file, line))
			file_content.push_back(line);
		file.close();
	}else{
		cout << "There was some error opening the file!\n";
		exit(1);
	}

	if(file_content.size() <= 1) {
		cout << "The file has no content!\n";
		exit(1);
	}

	vector<SpotifySong> v = parse_songs(file_content);
	pyramid_sort(v);
	for(SpotifySong x : v){
		x.print_song();
	}

	return 0;

}
