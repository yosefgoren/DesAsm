%{
	#include <stdio.h>
	#include <stdlib.h>
	#include <string>
	#include <vector>
	#include "build/parser.tab.hpp"
	void yyerror(const char* err);

	#define RET_TOK_GENERIC(token, action) {printf("token '"#token"'\n"); action return token;}
	#define RET_TOK(token) RET_TOK_GENERIC(token, )
	#define RET_TXT_TOK(token) RET_TOK_GENERIC(token, yylval.text = new std::string(yytext);)
%}

%option noyywrap
%option yylineno

id			([a-zA-Z][a-zA-Z0-9]*)
number		((([1-9][0-9]*)|0)(\.[0-9]+)?)
whitespace  ([\t\n\r ])
comment 	(#[^\n\r]*)
filename	(\"[a-zA-Z0-9_\-\. ]+\")
%%

curve	RET_TOK(CURVE)
let		RET_TOK(LET)
func	RET_TOK(FUNC)
show	RET_TOK(SHOW)
wait	RET_TOK(WAIT)
import	RET_TOK(IMPORT)
for		RET_TOK(FOR)
in		RET_TOK(IN)
speed	RET_TOK(SPEED)
:		RET_TOK(COLON)
,		RET_TOK(COMMA)
=		RET_TOK(EQ)
\-		RET_TOK(MINUS)

{filename} 	RET_TXT_TOK(FILENAME)
{comment} 	{printf("commnet\n");}
{id}		RET_TXT_TOK(ID)
{number}	RET_TXT_TOK(NUMBER)
~ return AND_ALSO;
\(	RET_TOK(LPAREN)
\)	RET_TOK(RPAREN)
\[	RET_TOK(LBRACE)
\]	RET_TOK(RBRACE)
\.	RET_TOK(DOT)
\+	RET_TXT_TOK(BINOP)
\*	RET_TOK_GENERIC(BINOP, yylval.text = new std::string("\\cdot");)
\/	RET_TXT_TOK(BINOP)
\^	RET_TXT_TOK(BINOP)


{whitespace}	;
.	{
		char msg_buf[0x1000];
		snprintf(msg_buf, 0x1000, "at line %d: unexpected character: '%s'\n", yylineno, yytext);
		yyerror(msg_buf);
	};

%%
