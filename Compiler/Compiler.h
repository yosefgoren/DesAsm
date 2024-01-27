#pragma once
#include <string>
#include <vector>
#include <fstream>
#define YYDEBUG 0
extern int yylineno;

extern std::fstream lout;
const constexpr char* default_output_file_name = "..\\output.tex";

void redirectStdin(std::string input_filename);
int main(int argc, char** argv);
void compile(std::istream& is, std::ostream& os);