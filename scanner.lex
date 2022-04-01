%{
	#include "stdlib.h"
	#include <string>
	#include "utility.h"
	#include "parser.tab.hpp"
%}

%option noyywrap
%option yylineno

id	([a-zA-Z][a-zA-Z0-9]*)
number	([1-9][0-9]*)
whitespace  		([\t\n\r ])

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

{id}	{yylval.text = new std::string(yytext); return ID;}
{number}	{yylval.integer = atoi(yytext); return NUMBER;}	
\(	return LPAREN;
\)	return RPAREN;
\[	return LBRACE;
\]	return RBRACE;
\+	{yylval.binop = PLUS; return BINOP;}
\*	{yylval.binop = MULT; return BINOP;}
-	{yylval.binop = MINUS; return BINOP;}

{whitespace}	;
.	{printf("at line %d: unexpected character: \'%s\'\n", yytext, yylineno); exit(1);};

%%
