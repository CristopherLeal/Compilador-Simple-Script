#ifndef _SEMANCTIC_ANALYSIS_C_
#define _SEMANCTIC_ANALYSIS_C_

#include "analisador_semantico.h"

void Semantics(int rule){

	printf("%s\n", "semantico");
	t_attrib IDD0, IDU0, ID0; //Devem ser estaticos para serem mantidos durante as chamadas
	int name;
	pobject p;

	switch(rule){

		case 15: // DF -> function IDD NB ( LP ) : T B
				//EndBlock();
				break;
		case 11: //DT -> type IDD = struct NB { DC }
				//EndBlock();
				break;		

		case 69: //IDD -> id
				name = tokenSecundario;
				IDD0._.IDD.name= name; 

				if( (p = Search(name)) != NULL){
					Error(ERR_REDECL);
				}else
				{
					p = Define(name);
					printf("*****\ndefiniu %d\n",name);
				}
				IDD0._.IDD.obj = p;
			break;
			
		case 70: //IDU ->id
				name = tokenSecundario;
				IDU0._.IDU.name = name;

				if((p = Find(name)) == NULL){
					printf("*****\nusou %d\n",name);
					Error(ERR_NOT_DECL);
				}

				IDU0._.IDU.obj = p;

			break;
		case 71: //ID -> id
			name = tokenSecundario;
			IDU0._.IDU.name = name;
			IDU0._.IDU.obj = p;
			break;

		case 77: // NB -> ''
			NewBlock();
			break;	
						
	}
}



#endif










