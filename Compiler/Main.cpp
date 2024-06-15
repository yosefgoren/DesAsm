#include "Compiler.h"
#include "Prepr/Prepr.h"
#include "BrowserDisp/BrowserDisp.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void dump_file(const std::string& fname, const std::string& content) {
    // Open a file in write mode
    std::ofstream outfile(fname, std::ios::out | std::ios::trunc);

    // Check if the file is open
    if (!outfile.is_open()) {
        std::cerr << "Error opening file: " << fname << std::endl;
        return;
    }

    // Write the content to the file
    outfile << content;

    // Check for any I/O errors
    if (outfile.fail()) {
        std::cerr << "Error writing to file: " << fname << std::endl;
    }

    // Close the file
    outfile.close();
}

int main(int argc, char** argv){
	string input_filename = "..\\DasmExamples\\example.ds";
	const char* output_filename = nullptr;

	if(argc > 1){
		input_filename = argv[1];
	}
	if(argc > 2) {
		output_filename = argv[2];
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
	std::string json_content = compile(dasm_text.c_str(), printstdlib, output_filename == nullptr);
	cout << endl << "compilation finished succesfully." << endl;

	if(output_filename == nullptr) {
		//display the compiled result:
		printf("displaying in browser...\n");
		display_json(json_content);
	} else {
		printf("generating output file: '%s'...\n", output_filename);
		dump_file(output_filename, json_content);
	}

	return 0;
}