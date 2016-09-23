#ifndef _LEXICAL_ANALYSIS_C_
#define _LEXICAL_ANALYSIS_C_

#include "analisador_lexico.h"


static FILE * file;
int nNumIds=0;
int nNumConsts=0;
int init_file(char * filename){
	file = fopen(filename,"r");
	if(file != NULL);
		return 1;
	printf("%s\n","ERROR:ARQUIVO NAO ENCONTRADO");		
}

void finish_file(){
	fclose(file);
}

char readChar(void){
	char c;
	int len;
	len=fread (&c, sizeof(char), 1, file);
	if(len==0){
		return EOF;
	}
	
	return c;
}

int binarySearch(const char * words[], char *key , int len){
	int inf=0;
	int sup = len-1;
	int med;
	int cmp=0;
	while(inf <= sup){
		med = (inf + sup)/2;
		cmp = strcmp(key,words[med]);
		if(cmp == 0)
			return med;
		if(cmp < 0)
			sup = med-1;
		else
			inf = med+1;
	}
	return -1;
}

int sequencialSearch(const char * words[], char *key , int len){
	int i,cmp;
	for(i=0 ; i< len ; i++){
		cmp = strcmp(key,words[i]);
		if(cmp == 0)
			return i;
	}
	return -1;
}

t_token searchKeyWord( char *name ){
	int res = binarySearch(keyWords,name,TOT_RESERVED);
	if(res != -1)
		return (t_token)res;
	return ID;
}

int addIdentifier(char * name){
	int len = strlen(name);
	if(nNumIds < MAX_IDENTIFIERS && len > 0){
		ids[nNumIds]= (char*)malloc(len*sizeof(char));
			if(ids[nNumIds]!=NULL){
				strcpy(ids[nNumIds],name);
				return nNumIds++;
			}
	}
}

int searchName( char *name ){

	//printf("\n\nsearchName : %s\n",name );

	int res = sequencialSearch(ids,name,nNumIds);
	//printf("id %d\n\n", res );
	//printf("nNumIds %d\n", nNumIds );
	int i;

	//for(i=0 ; i< nNumIds ; i++){
	//	printf("%s\n", ids[i]);
	//}

	if(res >= 0){
		return res;
	}
	return addIdentifier(name);
}

int addCharConst(char c){
	 vConsts[nNumConsts].type=0;
	 vConsts[nNumConsts].cVal=c;
	 nNumConsts++;
	 return nNumConsts -1;
}

int addIntConst(int i){
	 vConsts[nNumConsts].type=1;
	 vConsts[nNumConsts].nVal=i;
	 nNumConsts++;
	 return nNumConsts -1;
}

int addStringConst(char * s){
	 vConsts[nNumConsts].type=2;
	 //alocar no heap
	 char * p = (char*)malloc(strlen(s)*sizeof(char));
	 strcpy(p,s);
	 vConsts[nNumConsts].sVal=p;
	 nNumConsts++;
	 return nNumConsts -1;
}

char getCharConst(int n){
	return vConsts[n].cVal;
}

int getIntConst(int n){
	return vConsts[n].nVal;
}

char * getStringConst(int n){
	return vConsts[n].sVal;
}

void free_strings(){
	int i;
	for(i=0;i<nNumConsts;i++){
		if(vConsts[i].type == 2)
			free(vConsts[i].sVal);
	}
}

char nextChar ='\x20';

t_token nextToken(){

	while(isspace(nextChar)){
		nextChar = readChar();
	}

	if(nextChar==EOF)
		return EOF_;
	
	if(isalpha(nextChar)){
		char text[MAX_ID_LEN+1];
		int i=0;
		do{
			text[i++] = nextChar;
			nextChar = readChar();
		}
		while(isalnum(nextChar) || nextChar == '_');
		text[i]='\0';

		token = searchKeyWord(text);
		if(token == ID){
			tokenSecundario = searchName(text);
		}
	}
	else if(isdigit(nextChar)){
		char numeral[MAX_NUM_LEN+1];
		int i=0;
		do{
			numeral[i++]=nextChar;
			nextChar=readChar();
		}
		while(isdigit(nextChar));
		numeral[i]='\0';
		token = NUMERAL;
		tokenSecundario =  addIntConst(atoi(numeral));
	}
	else if(nextChar == '\'' ){
		nextChar = readChar();
		token =CHARACTER;
		tokenSecundario = addCharConst(nextChar);
		nextChar = readChar(); //scape \'
		nextChar= readChar();
	}
	else if(nextChar == '\"' ){	
		char string[MAX_STR_LEN+1];
		int i=0;
		do{
			string[i++] =nextChar;
			nextChar = readChar();
		}
		while(nextChar != '\"');
		nextChar=readChar();
		string[i]='\0';

		token = STRINGVAL;
		tokenSecundario = addStringConst(string+1); //scape \" caractere
	}
	else 
		switch(nextChar){
			case ':':
				nextChar = readChar();
				token = COLON;
				break;
			case ';':
				nextChar = readChar();
				token =SEMI_COLON ;
				break;
			case ',':
				nextChar = readChar();
				token = COMMA ;
				break;		
			case '[':
				nextChar = readChar();
				token = LEFT_SQUARE ;
				break;
			case ']':
				nextChar = readChar();
				token = RIGHT_SQUARE ;
				break;
			case '{':
				nextChar = readChar();
				token = LEFT_BRACES ;
				break;
			case '}':
				nextChar = readChar();
				token = RIGHT_BRACES ;
				break;
			case '(':
				nextChar = readChar();
				token = LEFT_PARENTHESIS ;
				break;
			case ')':
				nextChar = readChar();
				token = RIGHT_PARENTHESIS ;
				break;
			case '*':
				nextChar = readChar();
				token = TIMES ;
				break;
			case '/':
				nextChar = readChar();
				token = DIVIDE ;
				break;
			case '.':
				nextChar = readChar();
				token = DOT ;
				break;
			case '&':
				nextChar = readChar();
				if(nextChar == '&'){
					token = AND;
					nextChar = readChar();
				}
				break;											
			case '|':
				nextChar = readChar();
				if(nextChar == '|'){
					token = OR;
					nextChar = readChar();
				}
				break;
			case '<':
				nextChar = readChar();
				if(nextChar == '='){
					token = LESS_OR_EQUAL;
					nextChar = readChar();
				}
				else
					token = LESS_THAN;
				break;
			case '>':
				nextChar = readChar();
				if(nextChar == '='){
					token = GREATER_OR_EQUAL;
					nextChar = readChar();
				}
				else
					token = GREATER_THAN;
				break;
			case '=':
				nextChar = readChar();
				if(nextChar == '='){
					token = EQUAL_EQUAL;
					nextChar = readChar();
				}
				else
					token = EQUALS;
				break;
			case '!':
				nextChar = readChar();
				if(nextChar == '='){
					token = NOT_EQUAL;
					nextChar = readChar();
				}
				else
					token = NOT;
				break;	
			case '+':
				nextChar = readChar();
				if(nextChar == '+'){
					token = PLUS_PLUS;
					nextChar = readChar();
				}
				else
					token = PLUS;
				break;			
			case '-':
				nextChar = readChar();
				if(nextChar == '-'){
					token = MINUS_MINUS;
					nextChar = readChar();
				}
				else
					token = MINUS;
				break;		
			default:
				token = UNKNOWN;
		}

	return token;
}

#endif