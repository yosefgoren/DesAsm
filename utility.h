#pragma once
#include <string>
#include <vector>
#include <fstream>
#define YYDEBUG 0
extern int yylineno;

extern std::fstream lout;
const constexpr char* default_output_file_name = "..\\output.tex";

void outputLatex(std::string content);
void redirectStdin(std::string input_filename);
int main(int argc, char** argv);