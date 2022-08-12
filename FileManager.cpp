#include "FileManager.h"
#include <iostream>
#include <exception>

using namespace std;

FileManager::FileManager(FILE** managed_file)
		:managed_file(managed_file),initial_file_value(*managed_file){}

void FileManager::pushInputFile(string input_filename){
	if(isFileOpened(input_filename))
		throw runtime_error("file named: " + input_filename + "already opened");
	open_files.push_back(InputFile());
	open_files.back().filename = input_filename;
	
	//open the new input file and assign it to top file in stack:
	open_files.back().fobject = fopen(input_filename.c_str(), "r");

	//throw exception if file could not be opened:
	if(open_files.back().fobject == NULL)
		throw runtime_error("file named: " + input_filename + " not found");

	//set the managed file to point at the newly opened file:
	*managed_file = open_files.back().fobject;
}

void FileManager::popInputFile(){
	if(open_files.size() == 0)
		throw "no file to pop";
	//close file at top of stack:
	fclose(open_files.back().fobject);

	//pop top file off stack:
	open_files.pop_back();

	//if stack is now empty, redirect 'managed_file' to new top file:
	if(open_files.size() == 0)
		*managed_file = initial_file_value;
	else //otherwise, set managed file to new top of stack:
		*managed_file = open_files.back().fobject;
}

bool FileManager::isEmpty() const{
	return open_files.size() == 0;
}

bool FileManager::isFileOpened(std::string filename) const{
	for(int i = 0; i < open_files.size(); i++){
		if(open_files[i].filename == filename)
			return true;
	}
	return false;
}