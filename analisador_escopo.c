#ifndef _SCOPE_ANALYSIS_C_	 
#define _SCOPE_ANALYSIS_C_

#include "analisador_escopo.h"

int NewBlock(void){
	SymbolTable[++nCurrentLevel] = NULL;
	SymbolTableLast[nCurrentLevel] = NULL;
	return nCurrentLevel;
}

int EndBlock(void){
	return --nCurrentLevel;
}

pobject Define(int aName){

	pobject obj = (pobject)malloc(sizeof(object));


	obj->nName = aName;
	obj->pNext =NULL;

	if(SymbolTable[nCurrentLevel] == NULL){

		SymbolTable[nCurrentLevel] = obj;
		SymbolTableLast[nCurrentLevel] = obj;

	}
	else{

		SymbolTableLast[nCurrentLevel]->pNext = obj;
		SymbolTableLast[nCurrentLevel] = obj;
	}


	return obj;
}

pobject Search(int aName){

	pobject obj = SymbolTable[nCurrentLevel];
	while( obj != NULL){		
		if(obj->nName == aName)
			break;
		else
			obj = obj->pNext;
	}
	return obj;
}

pobject Find(int aName){

	int i;
	pobject obj = NULL;

	for( i =  nCurrentLevel ; i >= 0 ; --i ){

		obj = SymbolTable[i];

		while( obj != NULL){

			if( obj->nName == aName)
				break;
			else 
				obj = obj->pNext;
		}

		if( obj != NULL) break;
	}
	return obj;
}



#endif

