#include "Compiler/Exceptions.h"
using namespace std;

InternalError::InternalError(const string& msg)
	:msg(msg){}