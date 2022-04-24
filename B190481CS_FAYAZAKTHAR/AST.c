#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "AST.h"
#include "LST.h"




ASTNode* Create_node(int type, int nodetype, char *name, int val, ASTNode *arglist, ASTNode *ptr1, ASTNode *ptr2, ASTNode *ptr3)
{
    ASTNode *temp = (ASTNode*)malloc(sizeof(ASTNode));
    temp->type = type;
    temp->nodetype = nodetype;
    if(name == NULL)
    {
        temp->name = name;
    }
    else
    {
        temp->name = (char *)malloc(sizeof(name));
        strcpy(temp->name,name);
    }
    temp->val = val;
    temp->arglist = arglist;
    temp->ptr1 = ptr1;
    temp->ptr2 = ptr2;
    temp->ptr3 = ptr3;
    
    return temp;
}

void pre_order_traversal(ASTNode *head){
    if (head == NULL){
        return ;
    }
    printf("%d\n",head->nodetype);
    if (head->Lentry != NULL){
        printf("Lsymbol binding is %d\n",head->Lentry->binding);
    }
    pre_order_traversal(head->ptr1);
    pre_order_traversal(head->ptr2);
    pre_order_traversal(head->ptr3);
}
 



