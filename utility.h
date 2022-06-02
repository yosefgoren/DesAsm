#ifndef UTILITY_H
#define UTILITY_H
#include <string>
#include <vector>

extern int yylineno;

void redirectStdin(std::string input_filename);
int main(int argc, char** argv);

#endif