#include "Prepr/CinManager.h"
#include <iostream>
#include <string>
#include <set>

using namespace std;

/**
 * print all lines from cin to cout untill eof.
 */
void printAllCin(){
	string line;
	while(getline(cin, line))
		cout << line << endl;
}

vector<string> tokenize(string line){
	vector<string> tokens;
	string token;
	for(int i = 0; i < line.size(); i++){
		if(line[i] == ' '){
			tokens.push_back(token);
			token = "";
		}
		else
			token += line[i];
	}
	tokens.push_back(token);
	return tokens;
}

set<string> imported_files = {};

void recursiveRead(string initial_filename, ostream& out){
	CinManager im(initial_filename);

	string line;
	string filename;
	while(!im.isEmpty()){
		while(getline(cin, line)){
			//check if line contains 'import', if so set 'filename' to the next word:
			vector<string> tokens;
			tokens = tokenize(line);
			if(tokens.size() > 1 && tokens[0] == "import"){
				filename = tokens[1];
				if(imported_files.count(filename) == 0){
					if(filename.size() < 3)
						throw runtime_error("expected \"<filename>\" name after 'import' command.");
					//remove '"' from filename start and ending:
					filename = filename.substr(1, filename.size()-2);
					//add "..\"	to filename:
					filename = "..\\" + filename;
					//start importin from new file:
					cout << "changing import src to: " << filename << endl;//DB
					imported_files.insert(filename);
					im.pushInputFile(filename);
				}
			} else {
				out << line + "\n";
			}
		}
		im.popInputFile();
	}
}

bool canOpenFile(string filename, ios::openmode mode){
	ifstream file(filename, mode);
	if(file.is_open()){
		file.close();
		return true;
	}
	return false;
}

int main(int argc, char** argv){
	if(argc < 3){
		cout << "usage: " << argv[0] << " <input_filename> <output_filename>" << endl;
		return 0;
	}
	string input_filename = argv[1];
	if(!canOpenFile(input_filename, ios::in)){
		cout << "file named: " << input_filename << " could not be opened" << endl;
		return 0;	
	}
	string output_filename = argv[2];
	fstream out(output_filename, ios::out);
	if(!out.is_open()){
		cout << "file named: " << output_filename << " could not be opened" << endl;
		return 0;	
	}
	
	recursiveRead(input_filename, out);
}