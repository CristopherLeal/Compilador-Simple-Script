#ifndef _ALERTA_ERRO_H_
#define _ALERTA_ERRO_H_

#include <stdio.h>
#include <stdlib.h>

#define ERR_REDECL 0
#define ERR_NOT_DECL 1

static char * erro_msg[]={
	"redeclaracao de identificador",
	"identificador nao declarado"
};

extern void Error(int erro_code);

#endif
