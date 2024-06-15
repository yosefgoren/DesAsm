#include "Expr.h"

const map<Expr::ValueType, const char*> Expr::type_names = {
    {Int, "Int"},
    {Number, "Number"},
    {List, "List"},
    {Vector, "Vector"},
    {Any, "Any"}
};

const map<Expr::ValueType, bool> Expr::could_be_Int = {
    {Int, true},
    {Number, true},
    {List, false},
    {Vector, false},
    {Any, true}
};
const map<Expr::ValueType, bool> Expr::could_be_Real = {
    {Int, false},
    {Number, true},
    {List, false},
    {Vector, false},
    {Any, true}
};
const map<Expr::ValueType, bool> Expr::could_be_List = {
    {Int, false},
    {Number, false},
    {List, true},
    {Vector, false},
    {Any, true}
};
const map<Expr::ValueType, bool> Expr::could_be_Vector = {
    {Int, false},
    {Number, false},
    {List, false},
    {Vector, true},
    {Any, true}
};
const map<Expr::ValueType, bool> Expr::could_be_Any = {
    {Int, true},
    {Number, true},
    {List, true},
    {Vector, true},
    {Any, true}
};

const map<Expr::ValueType, const map<Expr::ValueType, bool>&> Expr::could_be_tbl = {
    {Int, could_be_Int},
    {Number, could_be_Real},
    {List, could_be_List},
    {Vector, could_be_Vector},
    {Any, could_be_Any}
};