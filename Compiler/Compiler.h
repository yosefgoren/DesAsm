#pragma once
#include "CodeGenerator.h"
#include <string>
#include <vector>
#define YYDEBUG 0
extern int yylineno;

extern std::string latex_buf;
extern CodeGenrator gen;

void redirectStdin(std::string input_filename);
int main(int argc, char** argv);
std::string compile(const char* input_dasm, bool printstdlib);