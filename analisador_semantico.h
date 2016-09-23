
#ifndef _SEMANCTIC_ANALYSIS_H_
#define _SEMANCTIC_ANALYSIS_H_

#include "analisador_sintatico.h"
#include "analisador_lexico.h"
#include "alerta_erro.h"

typedef struct object{
	int nName;
	struct object *pNext;

} object , *pobject;

typedef struct attr{

	union{

		struct{
			int name;
			pobject obj;		
		}ID,IDU,IDD;

	}_;

}t_attrib;

extern void Semantics(int rule);




















#endif