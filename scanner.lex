%{
	#include "parser.tab.hpp"
	#include "stdlib.h"
	#include "string.h"
%}

%option noyywrap
%option yylineno

global_id	([A-Z][a-zA-Z]*)
local_id	([a-z_]+)
number	([1-9][0-9]*)

%%

curve	return CURVE;
display	return DISPLAY;
int	return INT;
real	return REAL;
pair	return PAIR;
t	return T;
pi	return PI;
~	return IS_A;
:	return COLON;
\+	{yylval.binop = PLUS; return BINOP;}
\*	{yylval.binop = MULT; return BINOP;}
-	{yylval.binop = MINUS; return BINOP;}
{global_id}	{yylval.text = alloCloneStr(yytext); return GlobalId;}
{local_id}	{yylval.text = alloCloneStr(yytext); return LocalId;}
{number}	{yylval.integer = atoi(yytext); return NUMBER;}	
\(	return LPAREN;
\)	return RPAREN;
\[	return LBRACE;
\]	return RBRACE;

%%