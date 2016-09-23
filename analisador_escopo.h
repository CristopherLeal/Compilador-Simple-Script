#ifndef _SCOPE_ANALYSIS_H_	 
#define _SCOPE_ANALYSIS_H_

#include <stdlib.h>
#include "analisador_semantico.h"

#define MAX_NEST_LEVEL 10


pobject SymbolTable[MAX_NEST_LEVEL];
pobject SymbolTableLast[MAX_NEST_LEVEL]; 
static 	int 	nCurrentLevel =0;

extern int NewBlock(void);
extern int EndBlock(void);
extern pobject Define(int);
extern pobject Search(int);
extern pobject Find(int);


#endif