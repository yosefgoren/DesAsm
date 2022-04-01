#ifndef PRINTER_H
#define PRINTER_H

#include <string>
#include <vector>
#include "Statment.h"

std::string toDesmosName(const std::string& name);

void printFuncDecl(const std::string& name, const std::vector<std::string>& param_names, const Statment& statment);

#endif