#ifndef _SYNTACTIC_ANALYSIS_C_
#define _SYNTACTIC_ANALYSIS_C_

#include "analisador_sintatico.h"


void init_map(){ 
map[ARRAY]=6; 
map[BOOLEAN]=2; 
map[BREAK]=24; 
map[CHAR]=1; 
map[CONTINUE]=25; 
map[DO]=23; 
map[ELSE]=21; 
map[FALSE]=45; 
map[FUNCTION]=15;
map[IF]=20; 
map[INTEGER]= 0 ; 
map[OF]=9; 
map[RETURN]= 26;
map[STRING]=3; 
map[STRUCT]=11; 
map[TRUE]=44; 
map[TYPE]=4; 
map[VAR]=19; 
map[WHILE]=22; 
map[COLON]=14; 
map[SEMI_COLON]=10; 
map[COMMA]=18; 
map[EQUALS]=5; 
map[LEFT_SQUARE]=7; 
map[RIGHT_SQUARE]=8; 
map[LEFT_BRACES]=12; 
map[RIGHT_BRACES]=13; 
map[LEFT_PARENTHESIS]=16; 
map[RIGHT_PARENTHESIS]=17; 
map[AND]=27; 
map[OR]=28; 
map[LESS_THAN]=29; 
map[GREATER_THAN]=30; 
map[LESS_OR_EQUAL]=31; 
map[GREATER_OR_EQUAL]=32; 
map[NOT_EQUAL]=34; 
map[EQUAL_EQUAL]=33; 
map[PLUS]=35; 
map[PLUS_PLUS]=39; 
map[MINUS]=36; 
map[MINUS_MINUS]=40; 
map[TIMES]=37; 
map[DIVIDE]=38; 
map[DOT]=42; 
map[NOT]=41; 
map[CHARACTER]=46; 
map[NUMERAL]=48; 
map[STRINGVAL]=47; 
map[ID]=43;  
map[EOF_]=49;
}



void teste_sintatico(){

	init_file("programa.ss");
	init_out_file("saida");
	init_map();

	int p;
	int q =0;
	int r;
	Push(0);
	t_token a =nextToken();
	do{
		p = Action[q][map[a]];
		//printf("p:%d\n",p );
		//printf("Top:%d Token:%d Map %d\n", Top(), a, map[a]);
		//printf("Token %d\n",map[a] );
		if(IS_SHIFT(p)){
			Push(p);
			a= nextToken();
			//printf("Top:%d Token:%d Map %d\n", Top(), a, map[a]);
		}else
		if(IS_REDUCTION(p)){
			r = RULE(p);
			Pop(Len[r]);
			Push(Action[Top()][Left[r]]);
			//printf("Rule:%d  Left:%d Len:%d\n", r,Left[r],Len[r]);
			Semantics(r);
		}else{
			printf("%s\n","erro de sintaxe" );
			break;
		}
		q=Top();
		//show_stack();
	}while(p != FINAL);


	finish_file();
	free_strings();
}







#endif
