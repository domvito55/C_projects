/**
Armazena a estrutura de uma DirTable

@author Murilo Marques Marinho
@version 1.0
*/

#ifndef DIRTABLE_HEADER_GUARD
#define DIRTABLE_HEADER_GUARD

typedef struct DirTable{
	DirLine* firstLine;
} DirTable;

extern void freeDirTable(DirTable** dt);
extern void newDirTable(DirTable** dirTable);
extern void addDirLineToDirTable(DirTable** dirTable, DirLine** dirLine);

#endif
