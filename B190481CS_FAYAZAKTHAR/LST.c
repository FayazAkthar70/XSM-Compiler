#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LST.h"

int variableCount = 0;

void init(){
    char varname[4] = "argc" ;
    Lsymbol *temp = (Lsymbol*)malloc(sizeof(Lsymbol));
    temp->name = (char*)malloc(sizeof(varname));
    strcpy(temp->name,varname);
    temp->binding = -3;
    temp->next = head.next;
    head.next = temp;
}

Lsymbol* LLookup(char *name){
    Lsymbol* temp = head.next;
    while (temp){
        if (strcmp(name,temp->name) == 0){
            return temp;
        }
        else{
            temp = temp->next;
        }
    }
    return NULL;
}
// h:-1->
// h:-1->x:1->
//h:-1->y:2->x:1->
Lsymbol* LInstall(char *name){
    Lsymbol* x = LLookup(name);

    if (x){
        return x;
    }
    else{

        Lsymbol *temp = (Lsymbol*)malloc(sizeof(Lsymbol));
        temp->name = (char*)malloc(sizeof(char*));
        strcpy(temp->name,name);
        int binding;
        if (head.next->binding != -3)
            binding = head.next->binding + 1;
        else 
            binding = 1;
        temp->binding = binding;

        ++variableCount;

        temp->next = head.next;
        head.next = temp;
        return temp;
    }
}

