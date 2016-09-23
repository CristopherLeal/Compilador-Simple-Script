#ifndef _ALERTA_ERRO_C_
#define _ALERTA_ERRO_C_

#include "alerta_erro.h"

void Error(int erro_code){
	printf("%s\n",erro_msg[erro_code]);
	exit(1);
}

#endif
