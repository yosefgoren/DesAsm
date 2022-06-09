#include "utility.h"
#include <assert.h>
#include <iostream>
#include <cstdio>
#include "Symtab.h"
#include "parser.tab.hpp"
using namespace std;

void redirectStdin(string input_filename){
	freopen(input_filename.c_str(), "r", stdin);
}

int main(int argc, char** argv){
	string input_filename = "..\\example.ds";//later change to first argument if exists.
	if(argc > 1){
		input_filename = argv[1];
	}
	cout << "getting input script from: " << input_filename << endl << endl;
	// std::vector<std::string> open_files_stack = {input_filename};
	
	redirectStdin(input_filename);
	bool printlib = true;
	for(int i = 0; i < argc; ++i)
		if(argv[i] == "nolib")
			printlib = false;

	if(printlib){
		cout << "L_{0}\\left(x,y,t\\right)=\\frac{t-x}{y-x}" << endl;
		cout << "L_{1}\\left(x,y,t\\right)=\\left(1-t\\right)x+ty" << endl;
		cout << "L_{split}(t,k)=L_{0}(0,\\frac{1}{k},\\operatorname{mod}(t,\\frac{1}{k}))" << endl;
		cout << "L_{index}(t,k)=\\operatorname{floor}(kt)+1" << endl;
		cout << endl;
	}

	try{
		Symtab symtab = Symtab();
		#if(YYDEBUG == 1)
		yydebug = 1;
		#endif
		yyparse();
	} catch(const SemanticError& e){
		cout << "\nline " << yylineno << ": " << e.errorMsg() << endl;
	}
	cout << endl << "0" << endl;
	return 0;
}

void yyerror(const char* s){
	printf("\nsyntax error. line %d: %s\n", yylineno, s);
	exit(1);
}
