#ifndef PRINTER_H
#define PRINTER_H

#include "Compiler/Statment.h"
#include <string>
#include <vector>

std::string toDesmosName(const std::string& name);

void printFuncDecl(const std::string& name, const std::vector<std::string>& param_names, const Statment& statment);

#endif