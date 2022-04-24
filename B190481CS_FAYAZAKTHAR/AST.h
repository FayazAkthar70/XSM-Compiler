
#define BOOL 0
#define INT 1

#define ADD_NODE 1
#define MINUS_NODE 2
#define MUL_NODE 3
#define DIV_NODE 4
#define MOD_NODE 5
#define ASSIGN_NODE 6 
#define IS_EQUAL_NODE 7
#define GT_NODE 8
#define LT_NODE 9
#define GTE_NODE 10 
#define LTE_NODE 11 
#define NTE_NODE 13
#define IDENTIFIER_NODE 14
#define CONST_NODE 15
#define WHILE_NODE 17
#define IF_NODE 19
#define RET_NODE 22
#define ASG_NODE 23
#define STMTS_NODE 24
#define ARGC_NODE 25
#define FUNC_NODE 26
#define IF_ELSE_NODE 27

typedef struct ASTNode{
  int type;           //pointer to the type table entry
  int nodetype;                     //node type information,eg : NODETYPE_WHILE,NODETYPE_PLUS,NODETYPE_STMT etc
  char *name;                       //stores the variable/function name in case of variable/function nodes
  int val;
  struct ASTNode *arglist;          //pointer to the expression list given as arguments to a function call
  struct ASTNode *ptr1,*ptr2,*ptr3; //Subtrees of the node. (Maximum Subtrees for IF THEN ELSE)
  struct Gsymbol *Gentry;           //pointer to GST entry for global variables and functions
  struct Lsymbol *Lentry;           //pointer to the function's LST for local variables and arguements
}ASTNode;


ASTNode* Create_node(
int type,
int nodetype,
char *name,
int val,
ASTNode *arglist,
ASTNode *ptr1,
ASTNode *ptr2,
ASTNode *ptr3
);

void pre_order_traversal(ASTNode *head);