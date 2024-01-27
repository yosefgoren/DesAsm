#include "CinManager.h"
#include <iostream>
#include <exception>

using namespace std;

CinManager::CinManager(string initial_input_filename){
	original_cinbuf = cin.rdbuf();//save original cin
	
	open_files.push_back(InputFile());
	open_files.back().filename = initial_input_filename;
	open_files.back().stream.open(initial_input_filename, ios::in);
	cin.rdbuf(open_files.back().stream.rdbuf());//redirect cin to the file
}

void CinManager::pushInputFile(string input_filename){
	if(isFileOpened(input_filename))
		throw runtime_error("file named: " + input_filename + "already opened");
	open_files.push_back(InputFile());
	open_files.back().filename = input_filename;
	open_files.back().stream.open(input_filename, ios::in);
	if(!open_files.back().stream.is_open())
		throw runtime_error("file named: " + input_filename + " not found");
	cin.rdbuf(open_files.back().stream.rdbuf());//redirect cin to the file
}

void CinManager::popInputFile(){
	if(open_files.size() == 0)
		throw "no file to pop";
	open_files.pop_back();
	cin.rdbuf(open_files.back().stream.rdbuf());//redirect cin to the new top file
	if(open_files.size() == 0)
		cin.rdbuf(original_cinbuf);//restore cin to original cin
}

bool CinManager::isEmpty() const{
	return open_files.size() == 0;
}

bool CinManager::isFileOpened(std::string filename) const{
	for(int i = 0; i < open_files.size(); i++){
		if(open_files[i].filename == filename)
			return true;
	}
	return false;
}

