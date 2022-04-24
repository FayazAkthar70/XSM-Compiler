%{
 
#include<stdio.h>
#include<stdlib.h>
int yywrap();
#include "LAT.c"

int count = 2040;
int flag = 0;
extern FILE* yyin;
FILE* xsm_file;
FILE* xsm_file_new;

%}

%%

[A-Za-z][A-Za-z0-9]*:[\n]   {if (flag == 0) LabelInstall(yytext,count);}
[\n]    {if (flag==0)
            count += 2;
        else if (flag == 1)
            fprintf(xsm_file_new,"\n");
        }

[\t]    {if (flag == 1) fprintf(xsm_file_new,"\t");}
[ ]     {if (flag == 1) fprintf(xsm_file_new," ");}
[A-Za-z][A-Za-z0-9]*    {if (flag == 1 ){
                            int addr = LabelLookup(yytext);
                            if (addr != -1){
                                printf("The lookup addr is %d\n",addr);
                                fprintf(xsm_file_new,"%d",addr);
                            }
                            else
                                fprintf(xsm_file_new,"%s",yytext);
                            }
                        }
.   {if (flag ==1) fprintf(xsm_file_new,"%s",yytext); }
%%

int yywrap()
{
    if (flag==0){
        flag = 1;
        yyin = fopen("xsm_file.xsm", "r");
        return 0;
    }
    return 1;
}

int main(){
    yyin = fopen("xsm_file.xsm","r");
    xsm_file_new = fopen("B190481CS.xsm","w");
    yylex();
    LabelPrint(LabelHead);
}






