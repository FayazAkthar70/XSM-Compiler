#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LAT.h"

LabelEntry LabelHead;


LabelEntry* LabelInstall(char* label, int addr){
    LabelEntry* temp = LabelHead.next;
    while (temp){
        if (strncmp(label,temp->label, strlen(label) - 2) == 0)
            return temp;
        if (!temp->next)
            break;
        temp = temp->next;
    }
    LabelEntry *Label_node = (LabelEntry*)malloc(sizeof(LabelEntry));
    Label_node->next = NULL;
    Label_node->addr = addr;
    Label_node->label =  (char*)malloc(sizeof(label));
    strncpy(Label_node->label, label, strlen(label) - 2);
    Label_node->next = LabelHead.next;
    LabelHead.next = Label_node;
    return Label_node;

}


int LabelLookup (char* label){
    LabelEntry* temp = LabelHead.next;
    while (temp){
        if (strcmp(label,temp->label) == 0){
            return temp->addr;
        }
        else{
            temp = temp->next;
        }
    }
    return -1;
}
void LabelPrint(LabelEntry head){
    LabelEntry* temp = head.next; 
    while(temp != NULL){
        printf("label ->   %s\n",temp->label);
        printf("addr  ->  %d\n",temp->addr);
        temp = temp->next;
    }
}


