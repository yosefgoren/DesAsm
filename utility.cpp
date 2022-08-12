#include "utility.h"
#include "display_latex.h"
#include <assert.h>
#include <fstream>
#include <string>
#include <cstdio>
#include "Symtab.h"
#include <iostream>
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
	string input_filename = "..\\example.ds";

	if(argc > 1){
		input_filename = argv[1];
	}
	cout << "getting input script from: " << input_filename << endl << endl;
	// vector<pair<string, int>> open_files_stack = {{input_filename, 0}};
	
	bool printstdlib = true;
	for(int i = 0; i < argc; ++i)
		if(argv[i] == "nostdlib")
			printstdlib = false;
	
	lout.open(latex_output_filename, fstream::out);

	if(printstdlib)
		printStdLib();

	// while(open_files_stack.size() > 0){
		//get the top item from 'open_files_stack':
		string top_file = input_filename; //open_files_stack.back().first;
		redirectStdin(top_file);
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
		//open_files_stack.pop_back();
	// }
	cout << endl << "compilation finished succesfully." << endl;
	display_latex(latex_output_filename);
	return 0;
}

void yyerror(const char* s){
	printf("\nsyntax error. line %d: %s\n", yylineno, s);
	exit(1);
}
