int getreg();
void freereg();
int getlabel();
void header(FILE* target_file);



int codegen(struct ASTNode *t, FILE* targetfile);
void READ_NODE(FILE* targetfile);
void WRITE_NODE(FILE* targetfile);
void codegen_init(FILE* xsm_file);

