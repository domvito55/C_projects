/**
Cabecalho da elfprint.c

@version 1.2
@author Murilo M. Marinho

*/

#ifndef ELFPRINT_HEADER_GUARD
#define ELFPRINT_HEADER_GUARD

void elfPrintStrTab(FILE* fp, Elf32_Str** strr);

void elfPrintSimbolTable(FILE* fp, SimbolTable** st, UseTable** ut, Stab** s, char* start_label);

void elfPrintStab(FILE* fp, Stab** s);

int elfPrintText(FILE* fp, MCTable* mcTable, SimbolTable* simbolTable,int* end);

void elfPrintData(FILE *fp, DirTable* dirtable);

#endif
