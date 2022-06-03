#ifndef UTILITY_H
#define UTILITY_H
#include <string>
#include <vector>
#define YYDEBUG 0
extern int yylineno;

void redirectStdin(std::string input_filename);
int main(int argc, char** argv);

#endif