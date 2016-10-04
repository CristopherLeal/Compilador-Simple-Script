#include "analisador_lexico.h"
#include "analisador_sintatico.h"
#include "analisador_escopo.h"

void test_lexical(){

char * tokens[]={
// palavras reservadas
"ARRAY", "BOOLEAN", "BREAK", "CHAR", "CONTINUE", "DO", "ELSE", "FALSE", "FUNCTION","IF",
"INTEGER", "OF", "RETURN", "STRING", "STRUCT", "TRUE", "TYPE", "VAR", "WHILE",
// simbolos
"COLON", "SEMI_COLON", "COMMA", "EQUALS", "LEFT_SQUARE", "RIGHT_SQUARE",
"LEFT_BRACES", "RIGHT_BRACES", "LEFT_PARENTHESIS", "RIGHT_PARENTHESIS", "AND",
"OR", "LESS_THAN", "GREATER_THAN", "LESS_OR_EQUAL", "GREATER_OR_EQUAL",
"NOT_EQUAL", "EQUAL_EQUAL", "PLUS", "PLUS_PLUS", "MINUS", "MINUS_MINUS", "TIMES",
"DIVIDE", "DOT", "NOT",
// tokens regulares
"CHARACTER", "NUMERAL", "STRINGVAL", "ID",
// token deconhecido
"UNKNOWN",
"EOF_"};


	init_file("programa.ss");
	t_token token = -1;
	do{
		 token= nextToken();
		printf("%s",tokens[token]);
		if(token == ID){
			printf(" : %s",ids[tokenSecundario] );
		}else if(token == STRINGVAL){
			printf(" : %s", vConsts[tokenSecundario].sVal);
		}else if(token == NUMERAL){
			printf(" : %d", vConsts[tokenSecundario].nVal);
		}else if(token == CHARACTER){
			printf(" : %c", vConsts[tokenSecundario].cVal);
		}
		printf("\n");
	}while(token != EOF_);
	printf("%s\n","terminou" );
	finish_file();
	free_strings();
}


void teste_escopo(){
	printf("current level %d\n",NewBlock());
	Define(1);
	Define(2);
	printf("%d\n", Find(1)->nName);
	printf("%d\n", Find(2)->nName);
	//Search(1) != NULL ? Search(1) : 0
	printf("Search %d\n", Search(2) != NULL ? Search(2)->nName : 0 );
	printf("current level %d\n",NewBlock());
	Define(3);
	printf("%d\n", Find(3)->nName);
    printf("%d\n", Find(2)->nName);
    printf("Search %d\n", Search(2) != NULL ? Search(2)->nName : 0 );
    EndBlock();
    printf("Search %d\n", Search(2) != NULL ? Search(2)->nName : 0 );
	EndBlock();

}


void main(){

	//test_lexical();
	teste_sintatico();
	//teste_escopo();	

	/*
	object * o1, *o2,*o3;
	o1 = (object*)malloc(sizeof(malloc));
	o2 = (object*)malloc(sizeof(malloc));
	o3 = (object*)malloc(sizeof(malloc));
	o1->nName =1;
	o1->eKind =1;
	o1->nName =2;
	o1->eKind =2;
	o1->nName =3;
	o1->eKind =3;
	t_attrib t1, t2, t3, t;
	t1._.IDU.obj = o1;
	t2._.IDU.obj = o2;
	t3._.IDU.obj = o3;
	PushSem(t1);
	PushSem(t2);
	PushSem(t3);

	object * p;

	//t = TopSem(0);
	t = t1; 
	p = t._.IDU.obj;
	printf("%d\n",(int)p->nName ); 
	printf("%d\n",p->eKind ); */

}