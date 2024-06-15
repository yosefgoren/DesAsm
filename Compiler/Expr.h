#pragma once
#include <string>
#include <vector>
#include <map>

using namespace std;

struct Expr {
    enum ValueType {
        Int,
        Number,
        List,
        Vector,
        Any
    };

    string txt;
    ValueType type;
    vector<Expr*> elems;

    Expr(const string& txt, ValueType type)
        :txt(txt), type(type), elems(){}
    
    static const map<ValueType, bool> could_be_Int;
    static const map<ValueType, bool> could_be_Real;
    static const map<ValueType, bool> could_be_List;
    static const map<ValueType, bool> could_be_Vector;
    static const map<ValueType, bool> could_be_Any;
    
    static const map<ValueType, const map<ValueType, bool>&> could_be_tbl;

    static const map<ValueType, const char*> type_names;


    // Allocates an expression and deallocates the provided string
    static Expr* locxp(string* txt, ValueType type) {
        Expr* res = new Expr(*txt, type);
            delete txt;
        return res;
    }

    static string stringify_ls(const vector<Expr*>* ls) {
        string res;
        const string DELIM = ", ";
        for(int i = 0; i < ls->size(); ++i) {
            res += ls->at(i)->txt;
            if(i != ls->size()-1){
                res += DELIM;
            }
        }
        return res;
    }

    bool couldBe(ValueType prop_type) const {
        return could_be_tbl.at(type).at(prop_type);
    }
};