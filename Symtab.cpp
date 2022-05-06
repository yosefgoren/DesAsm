#include "Symtab.h"
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
	set<string> last_scope = nested_scopes.back();
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

const std::string& Symtab::defineAnonFunc(const std::string& sym, const std::vector<std::string>& params){
	if(table.count(sym) > 0)
		throw InternalError("cannot define anon function with symbol: '"+sym+"'");
	table[sym] = new SymInfo("a_{"+sym+"}");
	openScope(params);
	return table[sym]->getDsmExp();
}

const std::string& Symtab::SymInfo::getDsmExp() const{
	return dsm_exp;
}

Symtab::SymInfo::SymInfo(const std::string& dsm_exp)
	:dsm_exp(dsm_exp){}

const Symtab::SymInfo& Symtab::getSymInfo(const string& sym) const{
	if(table.count(sym) == 0)
		throw NoSuchSymException(sym);
	return *table.at(sym);
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

Symtab::SymInfo* Symtab::allocateSubscriptSymInfo(const std::string& sym){
	return new SymInfo(sym.substr(0,1) + "_{" + sym + "}");
}

void Symtab::openScope(const std::vector<std::string>& local_symbols){
	nested_scopes.push_back(set<string>());
	set<string>& new_scope = nested_scopes.back();
	for(auto sym: local_symbols){
		checkDefinable(sym);
		table[sym] = allocateSubscriptSymInfo(sym);
		new_scope.insert(sym);
	}
}