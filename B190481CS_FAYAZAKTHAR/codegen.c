#include <stdlib.h>
#include <stdio.h>
#include "AST.h"
#include "LST.h"
#include "codegen.h"

int REGMAX = 0;
int LABELMAX = 0;

int getlabel(){
    int temp = LABELMAX++;
    return temp;
}

int getreg(){
    if (REGMAX >= 20){
        printf("All registers are filled");
        exit (1);
    }
    int temp = REGMAX++;
    return temp;
}

void freereg(){
    REGMAX--;
}

void header(FILE* targetfile){
    fprintf(targetfile, "0\n2056\n0\n0\n0\n0\n0\n0\n");
}

void EXIT_NODE(FILE* targetfile){
        fprintf(targetfile, "MOV R0, 10\n");
        fprintf(targetfile, "PUSH R0\n");
        fprintf(targetfile, "PUSH R0\n");
        fprintf(targetfile, "PUSH R0\n");
        fprintf(targetfile, "PUSH R0\n");
        fprintf(targetfile, "PUSH R0\n");

        fprintf(targetfile, "INT 10\n");

        fprintf(targetfile, "POP R0\n");
        fprintf(targetfile, "POP R0\n");
        fprintf(targetfile, "POP R0\n");
        fprintf(targetfile, "POP R0\n");
        fprintf(targetfile, "POP R0\n");
}

void READ_NODE(FILE* targetfile){
        fprintf(targetfile, "MOV SP,4096\n");
        fprintf(targetfile, "MOV BP,4097\n");
        fprintf(targetfile, "PUSH R0\n");
        fprintf(targetfile, "MOV R0,7\n");
        fprintf(targetfile, "PUSH R0\n");
        fprintf(targetfile, "MOV R0,-1\n");
        fprintf(targetfile, "PUSH R0\n");
        fprintf(targetfile, "MOV R0,4096\n");
        fprintf(targetfile, "PUSH R0\n");
        fprintf(targetfile, "PUSH R0\n");
        fprintf(targetfile, "PUSH R0\n");

        fprintf(targetfile, "INT 6\n");

        fprintf(targetfile, "POP R0\n");
        fprintf(targetfile, "POP R0\n");
        fprintf(targetfile, "POP R0\n");
        fprintf(targetfile, "POP R0\n");
        fprintf(targetfile, "POP R0\n");
        fprintf(targetfile, "POP R0\n");
}

void WRITE_NODE(FILE* targetfile){
        fprintf(targetfile, "MOV R0,5\n");
        fprintf(targetfile, "PUSH R0\n");
        fprintf(targetfile, "MOV R0,-2\n");
        fprintf(targetfile, "PUSH R0\n");
        fprintf(targetfile, "MOV R0,[4096]\n");
        fprintf(targetfile, "PUSH R0\n");
        fprintf(targetfile, "PUSH R0\n");
        fprintf(targetfile, "PUSH R0\n");

        fprintf(targetfile, "INT 7\n");

        fprintf(targetfile, "POP R0\n");
        fprintf(targetfile, "POP R0\n");
        fprintf(targetfile, "POP R0\n");
        fprintf(targetfile, "POP R0\n");
        fprintf(targetfile, "POP R0\n");
        fprintf(targetfile, "POP R0\n");
}

void codegen_init(FILE* xsm_file){
    header(xsm_file),READ_NODE(xsm_file);
    int tempReg = REGMAX - 1;
    while(tempReg >= 0)
        fprintf(xsm_file, "PUSH R%d\n", tempReg--);
    fprintf(xsm_file,"MOV R0,[4096]\n");
    fprintf(xsm_file,"PUSH R0\n");
    fprintf(xsm_file,"PUSH R0\n");
    
    fprintf(xsm_file,"BRKP\n");
    fprintf(xsm_file,"CALL F0\n");

    tempReg = getreg();
    fprintf(xsm_file, "POP R%d\n",tempReg);
    fprintf(xsm_file, "POP R%d\n",getreg());
    freereg();
    int tempReg2 = 0;
    while(tempReg2 < REGMAX - 1)
        fprintf(xsm_file,"POP R%d\n",tempReg2++);

    fprintf(xsm_file,"MOV [4096],R%d\n",tempReg);
    WRITE_NODE(xsm_file);
    EXIT_NODE(xsm_file);
    fprintf(xsm_file,"F0:\n");
    fprintf(xsm_file, "BRKP\n");
    fprintf(xsm_file,"PUSH BP\n");
    fprintf(xsm_file,"MOV BP, SP\n");
    Lsymbol* temp = head.next;

    int i = variableCount;

    while(i > 0){
        fprintf(xsm_file,"PUSH R0\n");
        --i;
    }
}

int codegen(struct ASTNode *t, FILE* targetfile){
    int reg1, reg2, reg3, binding, Label1, Label2, temp, ret_val, temp_reg, arg1, temp_reg1, temp_reg2, j;
    printf("%d\n",t->nodetype);
    switch (t->nodetype)
    {
    case ADD_NODE:
        //  ADD_NODE
        //    /  \
        //   E    E
        reg1=codegen(t->ptr1, targetfile);
        reg2=codegen(t->ptr3, targetfile);

        if (t->ptr1->nodetype==IDENTIFIER_NODE)
            fprintf(targetfile, "MOV R%d,[R%d]\n",reg1,reg1);
        if (t->ptr3->nodetype==IDENTIFIER_NODE)
            fprintf(targetfile, "MOV R%d,[R%d]\n",reg2,reg2);
        
        fprintf(targetfile, "ADD R%d,R%d\n",reg1,reg2);
        freereg();
        return reg1;
    
    case MINUS_NODE:
        //  MINUS_NODE
        //      /\
        //     E  E
        reg1=codegen(t->ptr1, targetfile);
        reg2=codegen(t->ptr3, targetfile);

        if (t->ptr1->nodetype==IDENTIFIER_NODE)
            fprintf(targetfile, "MOV R%d,[R%d]\n",reg1,reg1);
        if (t->ptr3->nodetype==IDENTIFIER_NODE)
            fprintf(targetfile, "MOV R%d,[R%d]\n",reg2,reg2);

        fprintf(targetfile, "SUB R%d,R%d\n",reg1,reg2);
        freereg();
        return reg1;

    case MUL_NODE:
        //      MUL_NODE
        //        /\
        //       E  E
        reg1=codegen(t->ptr1, targetfile);
        reg2=codegen(t->ptr3, targetfile);
        if (t->ptr1->nodetype==IDENTIFIER_NODE)
            fprintf(targetfile, "MOV R%d,[R%d]\n",reg1,reg1);
        if (t->ptr3->nodetype==IDENTIFIER_NODE)
            fprintf(targetfile, "MOV R%d,[R%d]\n",reg2,reg2);

        fprintf(targetfile, "MUL R%d,R%d\n",reg1,reg2);
        freereg();
        return reg1;
    
    case DIV_NODE:
        //      DIV_NODE
        //        /\
        //       E  E
        reg1=codegen(t->ptr1, targetfile);
        reg2=codegen(t->ptr3, targetfile);

        if (t->ptr1->nodetype==IDENTIFIER_NODE)
            fprintf(targetfile, "MOV R%d,[R%d]\n",reg1,reg1);
        if (t->ptr3->nodetype==IDENTIFIER_NODE)
            fprintf(targetfile, "MOV R%d,[R%d]\n",reg2,reg2);

        fprintf(targetfile, "DIV R%d,R%d\n",reg1,reg2);
        freereg();
        return reg1;

    case MOD_NODE:
        //      MOD_NODE
        //        /\
        //       E  E
        reg1=codegen(t->ptr1, targetfile);
        reg2=codegen(t->ptr3, targetfile);

        if (t->ptr1->nodetype==IDENTIFIER_NODE)
            fprintf(targetfile, "MOV R%d,[R%d]\n",reg1,reg1);
        if (t->ptr3->nodetype==IDENTIFIER_NODE)
            fprintf(targetfile, "MOV R%d,[R%d]\n",reg2,reg2);

        fprintf(targetfile, "MOD R%d,R%d\n",reg1,reg2);
        freereg();
        return reg1;
    
    case ASSIGN_NODE:
        reg1 = codegen(t->ptr1, targetfile);
        reg2=codegen(t->ptr3, targetfile);

        // if (t->ptr1->nodetype==IDENTIFIER_NODE)
        //     fprintf(targetfile, "MOV R%d,[R%d]\n",reg1,reg1);

        printf("The reg2 val is%d\n",reg2);

        // if RHS is a variable or argc
        if (t->ptr3->nodetype == ARGC_NODE || t->ptr3->nodetype == IDENTIFIER_NODE)
             fprintf(targetfile,"MOV [R%d],[R%d]\n",reg1,reg2);
        else
            fprintf(targetfile,"MOV [R%d],R%d\n",reg1,reg2);

        freereg();
        return -1;
        break;

    case IS_EQUAL_NODE:
        reg1=codegen(t->ptr1, targetfile);
        reg2=codegen(t->ptr3, targetfile);

        if (t->ptr1->nodetype==IDENTIFIER_NODE)
            fprintf(targetfile, "MOV R%d,[R%d]\n",reg1,reg1);
        if (t->ptr3->nodetype==IDENTIFIER_NODE)
            fprintf(targetfile, "MOV R%d,[R%d]\n",reg2,reg2);

        fprintf(targetfile, "EQ R%d, R%d\n",reg1,reg2);
        freereg();
        return reg1;
        break;

    case GT_NODE:
        reg1=codegen(t->ptr1, targetfile);
        reg2=codegen(t->ptr3, targetfile);

        if (t->ptr1->nodetype==IDENTIFIER_NODE)
            fprintf(targetfile, "MOV R%d,[R%d]\n",reg1,reg1);
        if (t->ptr3->nodetype==IDENTIFIER_NODE)
            fprintf(targetfile, "MOV R%d,[R%d]\n",reg2,reg2);

        fprintf(targetfile, "GT R%d, R%d\n",reg1,reg2);
        freereg();
        return reg1;    
        break;

    case LT_NODE:
        reg1=codegen(t->ptr1, targetfile);
        reg2=codegen(t->ptr3, targetfile);
        fprintf(targetfile, "LT R%d,R%d\n",reg1,reg2);
        freereg();
        return reg1;    
        break;

    case GTE_NODE:
        reg1=codegen(t->ptr1, targetfile);
        reg2=codegen(t->ptr3, targetfile);

        if (t->ptr1->nodetype==IDENTIFIER_NODE)
            fprintf(targetfile, "MOV R%d,[R%d]\n",reg1,reg1);
        if (t->ptr3->nodetype==IDENTIFIER_NODE)
            fprintf(targetfile, "MOV R%d,[R%d]\n",reg2,reg2);

        fprintf(targetfile, "GE R%d,R%d\n",reg1,reg2);
        freereg();
        return reg1;    
        break;

    case LTE_NODE:
        reg1=codegen(t->ptr1, targetfile);
        reg2=codegen(t->ptr3, targetfile);

        if (t->ptr1->nodetype==IDENTIFIER_NODE)
            fprintf(targetfile, "MOV R%d,[R%d]\n",reg1,reg1);
        if (t->ptr3->nodetype==IDENTIFIER_NODE)
            fprintf(targetfile, "MOV R%d,[R%d]\n",reg2,reg2);

        fprintf(targetfile, "LE R%d,R%d\n",reg1,reg2);
        freereg();
        return reg1;    
        break;

    case NTE_NODE:
        reg1=codegen(t->ptr1, targetfile);
        reg2=codegen(t->ptr3, targetfile);

        if (t->ptr1->nodetype==IDENTIFIER_NODE)
            fprintf(targetfile, "MOV R%d,[R%d]\n",reg1,reg1);
        if (t->ptr3->nodetype==IDENTIFIER_NODE)
            fprintf(targetfile, "MOV R%d,[R%d]\n",reg2,reg2);

        fprintf(targetfile, "NE R%d,R%d\n",reg1,reg2);
        freereg();
        return reg1;    
        break;

    case IDENTIFIER_NODE:

        reg1 = getreg();
        fprintf(targetfile,"MOV R%d,BP\n",reg1);
        binding = (LLookup(t->name))->binding; 
        fprintf(targetfile,"ADD R%d,%d\n",reg1,binding);

        return reg1;

        break;

    case CONST_NODE:

        reg1 = getreg();

        fprintf(targetfile,"MOV R%d,%d\n",reg1,t->val);
        return reg1;

        break;

    case IF_NODE:
        Label1 = getlabel();
        reg1 = codegen(t->ptr1, targetfile);

        fprintf(targetfile, "JZ R%d,L%d\n",reg1, Label1);
        reg2 = codegen(t->ptr3, targetfile);
        fprintf(targetfile, "L%d:\n",Label1);

        // freereg();
        freereg();
        return -1;

    case IF_ELSE_NODE:
        Label1 = getlabel();
        Label2 = getlabel();
        reg1 = codegen(t->ptr1, targetfile);
        fprintf(targetfile, "JNZ R%d,L%d\n",reg1, Label1);
        reg2 = codegen(t->ptr2,targetfile);
        fprintf(targetfile, "JMP L%d\n", Label2);
        fprintf(targetfile,"L%d:\n",Label1);
        reg3 = codegen(t->ptr3,targetfile);
        fprintf(targetfile,"L%d:\n",Label2);

        freereg();
        freereg();
        // freereg();
        return -1;    

    case RET_NODE:
        temp = head.next->binding;
        temp_reg = getreg();
        while (temp-- > 0)
            fprintf(targetfile, "POP R%d\n",temp_reg);
        freereg();
        fprintf(targetfile, "BRKP\n");
        ret_val = codegen(t->ptr1,targetfile);
        reg1 = getreg();
        if (t->ptr1->nodetype==IDENTIFIER_NODE)
            fprintf(targetfile, "MOV R%d,[R%d]\n",ret_val,ret_val);
        fprintf(targetfile,"MOV R%d,BP\n",reg1);
        fprintf(targetfile,"SUB R%d,2\n",reg1);
        fprintf(targetfile, "MOV [R%d],R%d\n",reg1,ret_val);
        freereg();
        freereg();

        fprintf(targetfile, "MOV BP,[SP]\n");
        fprintf(targetfile, "POP R%d\n",temp_reg);
        fprintf(targetfile, "BRKP\n");
        fprintf(targetfile, "RET\n");
        return -1;

    case STMTS_NODE:
        codegen(t->ptr1,targetfile);
        codegen(t->ptr3,targetfile);
        return -1;
        break;

    case FUNC_NODE:
        temp = REGMAX-1;
        j = temp;
        while (temp >= 0)
            fprintf(targetfile, "PUSH R%d\n",temp--);

        fprintf(targetfile, "BRKP\n");

        arg1 = codegen(t->ptr1, targetfile);
        fprintf(targetfile, "PUSH R%d\n",arg1);

        fprintf(targetfile, "PUSH R%d\n",arg1);
        freereg();
        fprintf(targetfile, "CALL F0\n");
        fprintf(targetfile, "BRKP\n");
        
        ret_val = getreg();
        fprintf(targetfile,"POP R%d\n",ret_val);
    
        fprintf(targetfile,"POP R%d\n",getreg());
        freereg();

        temp = 0;
        while (temp <= j)
            fprintf(targetfile, "POP R%d\n",temp++ );

        return ret_val;
    }
}

