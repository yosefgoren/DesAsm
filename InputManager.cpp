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