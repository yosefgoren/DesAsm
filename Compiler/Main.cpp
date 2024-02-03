#include "Compiler.h"
#include "Prepr/Prepr.h"
#include "BrowserDisp/BrowserDisp.h"
#include <iostream>
using namespace std;

int main(int argc, char** argv){
	string input_filename = "..\\DasmExamples\\example.ds";

	if(argc > 1){
		input_filename = argv[1];
	}
	cout << "getting input script from: " << input_filename << endl << endl;
	// vector<pair<string, int>> open_files_stack = {{input_filename, 0}};
	
	bool printstdlib = true;
	for(int i = 0; i < argc; ++i)
		if(std::string(argv[i]) == "nostdlib")
			printstdlib = false;
	
	//call preprocessor from shell to create aggregated 'ppout.ds' file:
	string ppout_filename = "ppout.ds";
	string preprocessor_command = "Prepr.exe " + input_filename + " " + ppout_filename;
	int res = system(preprocessor_command.c_str());
	if(res != 0) {
		throw std::runtime_error("preprocessor failed with error code: "+std::to_string(res));
	}

	std::string dasm_text = read_file(ppout_filename);
	std::string json_content = compile(dasm_text.c_str(), printstdlib);
		
	cout << endl << "compilation finished succesfully." << endl;

	//display the compiled result:
	display_json(json_content);
	return 0;
}