#include "utility.h"
#include <assert.h>
#include <iostream>

string toDasmName(string name){
	assert(name.length() > 0);
	string res = name.substr(0,1);
	if(name.length() > 1)
		res += "_{"+name+"}";
	return res;
}