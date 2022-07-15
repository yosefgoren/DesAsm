#include <iostream>
#include <string>
#include <set>
#include "InputManager.h"

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

string recursiveRead(string initial_filename){
	InputManager im(initial_filename);
	string result;

	string line;
	string filename;
	while(!im.isEmpty()){
		// cout << "AA" << endl;//DB
		while(getline(cin, line)){
			// cout << "BB, line: " << line << endl;//DB
			result += line + "\n";
			//check if line contains 'import', if so set 'filename' to the next word:
			vector<string> tokens;
			tokens = tokenize(line);
			if(tokens.size() > 1 && tokens[0] == "import"){
				filename = tokens[1];
				cout << "importing file named: " << filename << endl;//DB
				if(imported_files.count(filename) == 0){
					if(filename.size() < 3)
						throw runtime_error("expected \"<filename>\" name after 'import' command.");
					//remove '"' from filename start and ending:
					filename = filename.substr(1, filename.size()-2);
					//add "..\"	to filename:
					filename = "..\\" + filename;
					//start importin from new file:
					// cout << "chaning import src to: " << filename << endl;//DB
					imported_files.insert(filename);
					im.pushInputFile(filename);
				}
			}
		}
		im.popInputFile();
	}
	return result;
}

int main(){
	cout << "starting inmanager test\n";
	string res = recursiveRead("..\\example.ds");
	cout << res << endl;
	cout << "finished inmanager test\n";
}