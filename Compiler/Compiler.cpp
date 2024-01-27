#include "Compiler/Compiler.h"
#include "BrowserDisp/BrowserDisp.h"
#include <assert.h>
#include <fstream>
#include <string>
#include <cstdio>
#include "Compiler/Symtab.h"
#include <iostream>
#include "Prepr/Prepr.h"
#include "build/parser.tab.hpp"
using namespace std;

void redirectStdin(string input_filename){
	freopen(input_filename.c_str(), "r", stdin);
}

/**
 * redirect stdout to file 'path'.
 */
void redirectStdout(string output_filename){
	freopen(output_filename.c_str(), "w", stdout);
}

void printStdLib(){
	lout << "L_{0}\\left(x,y,t\\right)=\\frac{t-x}{y-x}" << endl;
	lout << "L_{1}\\left(x,y,t\\right)=\\left(1-t\\right)x+ty" << endl;
	lout << "L_{split}(t,k)=L_{0}(0,\\frac{1}{k},\\operatorname{mod}(t,\\frac{1}{k}))" << endl;
	lout << "L_{index}(t,k)=\\operatorname{floor}(kt)+1" << endl;
	lout << endl;
}

int main(int argc, char** argv){
	string latex_output_filename = default_output_file_name;
	string input_filename = "..\\DasmExamples\\example.ds";

	if(argc > 1){
		input_filename = argv[1];
	}
	cout << "getting input script from: " << input_filename << endl << endl;
	// vector<pair<string, int>> open_files_stack = {{input_filename, 0}};
	
	bool printstdlib = true;
	for(int i = 0; i < argc; ++i)
		if(argv[i] == "nostdlib")
			printstdlib = false;
	
	//call preprocessor from shell to create aggregated 'ppout.ds' file:
	string ppout_filename = "ppout.ds";
	string preprocessor_command = "Prepr.exe " + input_filename + " " + ppout_filename;
	int res = system(preprocessor_command.c_str());
	if(res != 0) {
		throw std::runtime_error("preprocessor failed with error code: "+std::to_string(res));
	}

	//compile the aggregated 'ppout.ds' file and output result to 'output.tex':
	lout.open(latex_output_filename, fstream::out);

	if(printstdlib)
		printStdLib();

	redirectStdin(ppout_filename);
	try{
		Symtab symtab = Symtab();
		#if(YYDEBUG == 1)
		yydebug = 1;
		#endif
		yyparse();
	} catch(const SemanticError& e){
		cout << "\nline " << yylineno << ": " << e.errorMsg() << endl;
		exit(1);
	}
		
	cout << endl << "compilation finished succesfully." << endl;
	lout.close();

	//display the compiled result:
	display_latex(latex_output_filename);
	return 0;
}

void yyerror(const char* s){
	printf("\nsyntax error. line %d: %s\n", yylineno, s);
	exit(1);
}

void compile(std::istream& is, std::ostream& os) {
	
}