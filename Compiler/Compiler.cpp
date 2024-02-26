#include "Compiler/Compiler.h"
#include <assert.h>
#include <string>
#include <cstdio>
#include <iostream>
#include <memory>
#include "Compiler/Symtab.h"
#include "Compiler/CodeGenerator.h"
#include "build/parser.tab.hpp"
using namespace std;

std::string latex_buf;
CodeGenrator gen;
Symtab symtab;

void redirectStdin(string input_filename){
	// freopen(input_filename.c_str(), "r", stdin);
}

void printStdLib(){
	gen.addLatex("L_{0}\\left(x,y,t\\right)=\\frac{t-x}{y-x}");
	gen.addLatex("L_{1}\\left(x,y,t\\right)=\\left(1-t\\right)x+ty");
	gen.addLatex("L_{split}(t,k)=L_{0}(0,\\frac{1}{k},\\operatorname{mod}(t,\\frac{1}{k}))");
	gen.addLatex("L_{index}(t,k)=\\operatorname{floor}(kt)+1");
}

void yyerror(const char* s){
	throw std::runtime_error("syntax error. line "+std::to_string(yylineno)+": "+s);
}

//from: https://stackoverflow.com/questions/780676/string-input-to-flex-lexer
typedef struct yy_buffer_state *YY_BUFFER_STATE;
YY_BUFFER_STATE yy_scan_string(const char *str);

void resetGlobals() {
	gen.reset();
	symtab.reset();
	yylineno = 1;
}

std::string compile(const char* input_dasm, bool printstdlib, bool instructions_only){

	resetGlobals();

	if(printstdlib){
		printStdLib();
	}

	yy_scan_string(input_dasm);
	try{
		#if(YYDEBUG == 1)
		yydebug = 1;
		#endif
		yyparse();
	} catch(const SemanticError& e){
		throw runtime_error("Compilation Failed: line "+to_string(yylineno)+": "+e.errorMsg());
	}

	string output = instructions_only
		? gen.generate()
		: createJson({
			{"instructions", gen.generate()},
			{"intellisense", symtab.generateIntellisense()}
		});
	
	// printf("%s\n", output.c_str());
	return output;
}