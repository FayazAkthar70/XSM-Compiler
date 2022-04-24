typedef struct LabelEntry{
    char* label;
    int addr;
    struct  LabelEntry* next;
}LabelEntry;

LabelEntry* LabelInstall(char* label, int addr);
int LabelLookup (char* label);
void LabelPrint(LabelEntry head);