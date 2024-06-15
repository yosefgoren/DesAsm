%{
	#include <stdio.h>
	#include <stdlib.h>
	#include <string>
	#include <vector>
	#include "build/parser.tab.hpp"
	void yyerror(const char* err);
%}

%option noyywrap
%option yylineno

id			([a-zA-Z][a-zA-Z0-9]*)
number		((([1-9][0-9]*)|0)(\.[0-9]+)?)
whitespace  ([\t\n\r ])
comment 	(#[^\n\r]*)
filename	(\"[a-zA-Z0-9_\-\. ]+\")
%%

curve	return CURVE;
let	return LET;
func	return FUNC;
show	return SHOW;
wait	return WAIT;
import	return IMPORT;
for		return FOR;
in		return IN;
speed	return SPEED;
:	return COLON;
,	return COMMA;
=	return EQ;
\.x return GETX;
\.y return GETY;
\-	return MINUS;

{filename} {yylval.text = new std::string(yytext); return FILENAME;}
{comment} {;}
{id}	{yylval.text = new std::string(yytext); return ID;}
{number}	{yylval.text =new std::string(yytext); return NUMBER;}	
~ return AND_ALSO;
\(	return LPAREN;
\)	return RPAREN;
\[	return LBRACE;
\]	return RBRACE;
\+	{yylval.text = new std::string(yytext); return BINOP;}
\*	{yylval.text = new std::string("\\cdot"); return BINOP;}
\/	{yylval.text = new std::string(yytext); return BINOP;}
\^	{yylval.text = new std::string(yytext); return BINOP;}


{whitespace}	;
.	{
		char msg_buf[0x1000];
		snprintf(msg_buf, 0x1000, "at line %d: unexpected character: '%s'\n", yylineno, yytext);
		yyerror(msg_buf);
	};

%%
