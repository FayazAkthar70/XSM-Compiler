%{
 
#include<stdio.h>
#include<stdlib.h>
int yywrap();
#include "y.tab.h"
#include "AST.h"
#include "LST.h"
%}

%%

"FUN" {return FUNC;}
"while" {return WHILE;}
"do" {return DO;}
"for" {return FOR;}
"if"  {return IF;}
"else"  {return ELSE;}
"return" {return RETURN;}
"argc" {return ARGC;}
"read" {init();return READ;}
"write" {return WRITE;}
"break"	 { return BREAK; }

[a-zA-Z][a-zA-Z0-9]*  	{ yylval.node = Create_node(1,14, yytext, -1,NULL, NULL, NULL, NULL );return IDENTIFIER; }
[0-9]+ {yylval.node = Create_node(1, 15, NULL, atoi(yytext), NULL, NULL, NULL, NULL); return CONST;} 


"+"  {return ADD;}
"-"  {return MINUS;}
"*"  {return MUL;}
"/"  {return DIV;}
"%"  {return MOD;}

"=" {return ASSIGN;}
"==" {return IS_EQUAL;}
">" {return GT;}
"<" {return LT;}
">=" {return GTE;}
"<=" {return LTE;}
"!=" {return NTE;}


"(" {return *yytext;}
")" {return *yytext;}
"{" {return *yytext;}
"}" {return *yytext;}
";" {return *yytext;}

[\t] {;}
[\r\n] {;}
. {;}

%%

int yywrap()
{
  return 1;
}






