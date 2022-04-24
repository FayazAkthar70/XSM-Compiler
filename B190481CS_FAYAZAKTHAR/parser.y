%{
/*** Auxiliary declarations section ***/

#include<stdio.h>
#include<stdlib.h>
#include "AST.h"
#include "LST.h"
#include "codegen.h"

extern char yytext[];
#define YYDEBUG_LEXER_TEXT yytext

int yyerror(char const *s);
extern FILE* yyin;
FILE* xsm_file;

%}

%start Program
%union {struct ASTNode* node;}

%token FUNC WHILE DO FOR IF ELSE RETURN ARGC READ WRITE ADD MINUS MUL DIV MOD ASSIGN IS_EQUAL GT LT GTE LTE NTE CONST IDENTIFIER BREAK
%type <node> CONST IDENTIFIER E ProgRead ProgWrite Stmts Stmt AsgStmt IfStmt IfElseStmt RetStmt ProgArg ARGC




%right ASSIGN
%left IS_EQUAL NTE
%left GT LT GTE LTE
%left ADD MINUS
%left MUL DIV MOD


 /*** YACC Declarations section ***/

%%

/*** Rules Section ***/
Program : ProgRead ProgArg ProgWrite
;

ProgRead : READ '(' ARGC ')' ';' {}
;

ProgArg : ARGC ASSIGN FUNC '(' ARGC ')' '{' Stmts '}' { codegen_init(xsm_file);pre_order_traversal($8);printf("codegen started\n"); codegen($8,xsm_file);}
;

ProgWrite : WRITE '(' ARGC ')' ';' {}
;

Stmts   : Stmts Stmt  {$$ = Create_node(-1, STMTS_NODE, NULL, -1, NULL, $1, NULL, $2);}
	| Stmt	      {$$ = $1;}
;

Stmt    : AsgStmt   {$$ = $1;}
        | IfStmt    {$$ = $1;}
        | IfElseStmt    {$$ = $1;}
        | RetStmt   {$$ = $1;}
;

AsgStmt : IDENTIFIER ASSIGN E ';'  {printf("%s %d\n",$1->name,$1->nodetype);$1->Lentry = LInstall($1->name);$$ = Create_node(-1, ASSIGN_NODE, NULL, -1, NULL, $1, NULL, $3);}
;

IfStmt : IF '(' E ')' '{' Stmts '}' {$$ = Create_node(-1, IF_NODE, NULL, -1, NULL, $3, NULL, $6);}
;

IfElseStmt : IF '(' E ')' '{' Stmts '}' ELSE '{' Stmts '}'  {$$ = Create_node(-1, IF_ELSE_NODE, NULL, -1, NULL, $3, $10, $6);}
;

RetStmt : RETURN E ';' {$$ = Create_node(-1, RET_NODE, NULL, -1, NULL, $2, NULL, NULL);}
;

E   : E ADD E   {$$ = Create_node(INT, ADD_NODE, NULL, -1, NULL, $1, NULL, $3);}
    | E MUL E   {$$ = Create_node(INT, MUL_NODE, NULL, -1, NULL, $1, NULL, $3);}
    | E MINUS E {$$ = Create_node(INT, MINUS_NODE, NULL, -1, NULL, $1, NULL, $3);}
    | E DIV E {$$ = Create_node(INT, DIV_NODE, NULL, -1, NULL, $1, NULL, $3);}
    | E MOD E {$$ = Create_node(INT, MOD_NODE, NULL, -1, NULL, $1, NULL, $3);}
    | E GTE E   {$$ = Create_node(BOOL, GTE_NODE, NULL, -1, NULL, $1, NULL, $3);}
    | E LTE E   {$$ = Create_node(BOOL, LTE_NODE, NULL, -1, NULL, $1, NULL, $3);}
    | E GT E {$$ = Create_node(BOOL, GT_NODE, NULL, -1, NULL, $1, NULL, $3);}
    | E LT E {$$ = Create_node(BOOL, LT_NODE, NULL, -1, NULL, $1, NULL, $3);}
    | E IS_EQUAL E  {$$ = Create_node(BOOL, IS_EQUAL_NODE, NULL, -1, NULL, $1, NULL, $3);}
    | E NTE E   {$$ = Create_node(BOOL, NTE_NODE, NULL, -1, NULL, $1, NULL, $3);}
    | '(' E ')' {$$ = $2;}
    | CONST   {$$ = $1;}
    | IDENTIFIER   {$$ = $1;}
    | FUNC '(' E ')'   {$$ = Create_node(INT, FUNC_NODE, NULL, -1, NULL, $3, NULL, NULL);}
    | ARGC {$$ = Create_node(INT, IDENTIFIER_NODE, "argc", -1, NULL, NULL, NULL, NULL);}
;




%%

/*** Auxiliary functions section ***/
int yyerror(char const *s){
    printf("yyerror %s",s);
}

int main()
{
    /* yydebug =1; */
    /* yyin = fopen("input.txt","r"); */
    xsm_file = fopen("xsm_file.xsm", "w");
	yyparse();
	return 0;
}
 