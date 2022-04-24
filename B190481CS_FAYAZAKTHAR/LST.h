typedef struct Lsymbol{
  char *name;               //name of the variable
  int binding;              //stores memory address allocated to the variable 
  struct Lsymbol *next;     //points to the next Local Symbol Table entry
}Lsymbol;

Lsymbol* LLookup(char *name);
Lsymbol* LInstall(char *name);
void init();  

Lsymbol head ;
extern int variableCount;   // Keep track of number of variables
