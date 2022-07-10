#include "InputManager.h"
#include <iostream>

using namespace std;

void redirectStdin(string input_filename){
	freopen(input_filename.c_str(), "r", stdin);
}

InputManager::InputManager(string initial_input_filename){
	original_cinbuf = cin.rdbuf();//save original cin
	
	open_files.push_back(InputFile());
	open_files.back().filename = initial_input_filename;
	open_files.back().stream.open(initial_input_filename, ios::in);
	cin.rdbuf(open_files.back().stream.rdbuf());//redirect cin to the file
}

void InputManager::pushInputFile(string input_filename){
	if(isFileOpened(input_filename))
		throw "file already opened";
	open_files.push_back(InputFile());
	open_files.back().filename = input_filename;
	open_files.back().stream.open(input_filename, ios::in);
	cin.rdbuf(open_files.back().stream.rdbuf());//redirect cin to the file
}

void InputManager::popInputFile(){
	if(open_files.size() == 0)
		throw "no file to pop";
	open_files.pop_back();
	cin.rdbuf(open_files.back().stream.rdbuf());//redirect cin to the new top file
	if(open_files.size() == 0)
		cin.rdbuf(original_cinbuf);//restore cin to original cin
}

bool InputManager::isEmpty() const{
	return open_files.size() == 0;
}

bool InputManager::isFileOpened(std::string filename) const{
	for(int i = 0; i < open_files.size(); i++){
		if(open_files[i].filename == filename)
			return true;
	}
	return false;
}

