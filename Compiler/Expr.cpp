#include "Expr.h"

const map<Expr::ValueType, const char*> Expr::type_names = {
    {Int, "Int"},
    {Number, "Number"},
    {List, "List"},
    {Vector, "Vector"},
    {Func, "Func"},
    {Any, "Any"}
};

const map<Expr::ValueType, bool> Expr::could_be_Int = {
    {Int, true},
    {Number, true},
    {List, false},
    {Vector, false},
    {Func, false},
    {Any, true}
};
const map<Expr::ValueType, bool> Expr::could_be_Real = {
    {Int, false},
    {Number, true},
    {List, false},
    {Vector, false},
    {Func, false},
    {Any, true}
};
const map<Expr::ValueType, bool> Expr::could_be_List = {
    {Int, false},
    {Number, false},
    {List, true},
    {Vector, false},
    {Func, false},
    {Any, true}
};
const map<Expr::ValueType, bool> Expr::could_be_Vector = {
    {Int, false},
    {Number, false},
    {List, false},
    {Vector, true},
    {Func, false},
    {Any, true}
};
const map<Expr::ValueType, bool> Expr::could_be_Func = {
    {Int, false},
    {Number, false},
    {List, false},
    {Vector, false},
    {Func, true},
    {Any, true}
};
const map<Expr::ValueType, bool> Expr::could_be_Any = {
    {Int, true},
    {Number, true},
    {List, true},
    {Vector, true},
    {Func, false},
    {Any, true}
};

const map<Expr::ValueType, const map<Expr::ValueType, bool>&> Expr::could_be_tbl = {
    {Int, could_be_Int},
    {Number, could_be_Real},
    {List, could_be_List},
    {Vector, could_be_Vector},
    {Func, could_be_Func},
    {Any, could_be_Any}
};