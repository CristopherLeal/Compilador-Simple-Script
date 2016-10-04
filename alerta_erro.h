#ifndef _ALERTA_ERRO_H_
#define _ALERTA_ERRO_H_

#include <stdio.h>
#include <stdlib.h>

#define ERR_REDECL 0
#define ERR_NOT_DECL 1
#define ERR_INVALID_TYPE 2
#define ERR_KIND_NOT_VAR 3
#define	ERR_TYPE_EXPECTED 4 
#define ERR_TYPE_MISMATCH 5
#define ERR_BOOL_TYPE_EXPECTED 6
#define ERR_KIND_NOT_STRUCT 7
#define ERR_FIELD_NOT_DECL 8
#define ERR_KIND_NOT_ARRAY 9
#define ERR_INVALID_INDEX_TYPE 10
#define ERR_KIND_NOT_FUNC 11
#define ERR_TOO_MANY_ARGS 12
#define ERR_PARAM_TYPE 13
#define ERR_TOO_FEW_ARGS 14


static char * erro_msg[]={
	"redeclaracao de identificador",
	"identificador nao declarado",
	"operacao invalida sobre tipo",
	"o id nao se refere a uma variavel",
	"um tipo eh esperado",
	"tipo nao correspondentes",
	"esperado tipo boolean",
	"tipo nao eh struct",
	"campo nao declarado",
	"tipo nao eh array",
	"tipo do indice invalido",
	"tipo nao eh funcao",
	"argumentos demais",
	"tipo de parametro errado",
	"argumentos de menos"
};
extern void Error(int erro_code);

#endif
