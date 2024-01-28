#include "Compiler/Symtab.h"
using namespace std;

Symtab::Symtab()
	:anon_count(0){
	defineBuiltInSymbols();
}
Symtab::~Symtab(){
	for(pair<string, SymInfo*> key_value: table)
		delete key_value.second;
}

const string& Symtab::defineGlobalValue(const string& sym){
	checkDefinable(sym);

	SymInfo* info = allocateSubscriptSymInfo(sym);
	table[sym] = info;
	return info->getDsmExp();
}

void Symtab::closeScope(){
	if(nested_scopes.empty())
		throw InternalError("cannot close scope - no local scopes open");
	vector<string> last_scope = nested_scopes.back();
	for(auto sym: last_scope){
		delete table[sym];
		table.erase(sym);
	}
	nested_scopes.pop_back();
}

const string& Symtab::defineFunction(const std::string& sym, const std::vector<std::string>& params){
	checkDefinable(sym);
	table[sym] = allocateSubscriptSymInfo(sym);
	openScope(params);
	return table[sym]->getDsmExp();
}

string Symtab::getAnonSymbol(){
	return to_string(++anon_count);
}

const std::string& Symtab::defineAnonFunc(const std::string& sym, const std::vector<std::string>& new_params){
	if(table.count(sym) > 0)
		throw InternalError("cannot define anon function with symbol: '"+sym+"'");
	table[sym] = new SymInfo("a_{"+sym+"}");
	openScope(new_params);
	return table[sym]->getDsmExp();
}

const std::vector<std::vector<std::string>>& Symtab::getLocalScopes() const{
	return nested_scopes;
}

std::vector<std::string> Symtab::getVariables() const{
	vector<string> items;
	for(const vector<string>& scope: nested_scopes)
		for(const string& sym: scope)
			items.push_back(sym);
	return items;
}

std::string Symtab::getVariablesFormat(
		const std::vector<std::string> variables,
		const std::map<std::string, std::string>& replace, 
		const std::set<std::string> ignore
) const {
	vector<const string*> items;
	for(const string& sym: variables)
		if(ignore.count(sym) == 0)
			items.push_back(&sym);
	
	string res = "\\left(";
	for(const string* symp: items){
		const string& sym = *symp;
		res += replace.count(sym)>0 ? replace.at(sym) : getSymInfo(sym).getDsmExp();
		if(*(items.rbegin()) != symp)
			res += " , ";
	}
	res += "\\right)";
	return res;
}

std::string Symtab::getLocalsInFormat(const std::map<std::string, std::string>& replace
		, const std::set<std::string> ignore) const {
	return getVariablesFormat(getVariables(), replace, ignore);
	
	// vector<const string*> items;
	// for(vector<string>& scope: nested_scopes)
	// 	for(const string& sym: scope)
	// 		if(ignore.count(sym) == 0)
	// 			items.push_back(&sym);
	
	// string res = "\\left(";
	// for(const string* symp: items){
	// 	const string& sym = *symp;
	// 	res += replace.count(sym)>0 ? replace.at(sym) : getSymInfo(sym).getDsmExp();
	// 	if(*(items.rbegin()) != symp)
	// 		res += " , ";
	// }
	// res += "\\right)";
	// return res;
}

const std::string& Symtab::SymInfo::getDsmExp() const{
	return dsm_exp;
}

Symtab::SymInfo::SymInfo(const std::string& dsm_exp)
	:dsm_exp(dsm_exp){}

const Symtab::SymInfo& Symtab::getSymInfo(const string& sym) const{
	if(table.count(sym) == 0){
		throw NoSuchSymException(sym);
	}
	const SymInfo& s = *table.at(sym);
	return s;
}

Symtab::SymExistsException::SymExistsException(const string& sym)
	:sym(sym){}
Symtab::NoSuchSymException::NoSuchSymException(const string& sym)
	:sym(sym){}
string Symtab::SymExistsException::errorMsg() const{
	return "the symbol '"+sym+"' is already defined.";
}
string Symtab::NoSuchSymException::errorMsg() const{
	return "undefined symbol '"+sym+"'.";
}

void Symtab::defineBuiltInSymbols(){
	std::set<std::string> built_in_funcs = {
		"sin",
		"cos",
		"floor",
		"mod"
	};
	for(auto func_name: built_in_funcs)
		table[func_name] = new SymInfo("\\operatorname{"+func_name+"}");
	
	std::set<std::string> built_in_values = {
		"pi"
	};
	for(auto value_name: built_in_values)
		table[value_name] = new SymInfo("\\"+value_name);
}

void Symtab::checkDefinable(const std::string& sym){
	if(table.count(sym) > 1)
		throw SymExistsException(sym);
}

void Symtab::reset(){
	table.clear();
	nested_scopes.clear();
	anon_count = 0;

	defineBuiltInSymbols();
}

Symtab::SymInfo* Symtab::allocateSubscriptSymInfo(const std::string& sym){
	string dsm_exp = sym.substr(0,1);
	if(sym.length() > 1)
		dsm_exp += "_{" + sym + "}";
	return new SymInfo(dsm_exp);
}

void Symtab::openScope(const std::vector<std::string>& local_symbols){
	for(auto sym: local_symbols){
		checkDefinable(sym);
		table[sym] = allocateSubscriptSymInfo(sym);
	}
	nested_scopes.push_back(local_symbols);
}