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

std::string compile(const char* input_dasm, bool printstdlib){
	gen.reset();
	symtab.reset();
	if(printstdlib)
		printStdLib();

	// redirectStdin(tmp_filename);
	// printf("compiling	:\n%s\n", input_dasm);
	yy_scan_string(input_dasm);
	try{
		#if(YYDEBUG == 1)
		yydebug = 1;
		#endif
		yyparse();
	} catch(const SemanticError& e){
		fprintf(stderr, "Compilation Failed: line %d: %s", yylineno, e.errorMsg().c_str());
	}

	// printf("%s\n", gen.generate().c_str());
	return gen.generate();
}