#ifndef _LEXICAL_ANALYSIS_H_
#define _LEXICAL_ANALYSIS_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define TOT_RESERVED 19
#define MAX_IDENTIFIERS 100
#define MAX_CONSTS 100
#define MAX_ID_LEN 100
#define MAX_NUM_LEN 10
#define MAX_STR_LEN 100
#define MAX_TOKEN_TYPES 51

typedef unsigned char byte;

typedef enum {
// palavras reservadas
ARRAY, BOOLEAN, BREAK, CHAR, CONTINUE, DO, ELSE, FALSE, FUNCTION, IF,
INTEGER, OF, RETURN, STRING, STRUCT, TRUE, TYPE, VAR, WHILE,
// simbolos
COLON, SEMI_COLON, COMMA, EQUALS, LEFT_SQUARE, RIGHT_SQUARE,
LEFT_BRACES, RIGHT_BRACES, LEFT_PARENTHESIS, RIGHT_PARENTHESIS, AND,
OR, LESS_THAN, GREATER_THAN, LESS_OR_EQUAL, GREATER_OR_EQUAL,
NOT_EQUAL, EQUAL_EQUAL, PLUS, PLUS_PLUS, MINUS, MINUS_MINUS, TIMES,
DIVIDE, DOT, NOT,
// tokens regulares
CHARACTER, NUMERAL, STRINGVAL, ID,
// token deconhecido
UNKNOWN ,
EOF_} t_token;


typedef struct{
	byte type; // 0-char, 1-int, 2- string
	union{
		char cVal;
		int nVal;
		char *sVal;
		};
} t_const;

static char * keyWords[]={
	"array",
	"boolean",
	"break",
	"char",
	"continue",
	"do",
	"else",
	"false",
	"function",
	"if",
	"integer",
	"of",
	"return",
	"string",
	"struct",
	"true",
	"type",
	"var",
	"while"
};

char * ids[MAX_IDENTIFIERS];
int nNumIds;

t_const vConsts[MAX_CONSTS];
int nNumConsts;


extern char readChar(void);
extern t_token searchKeyWord( char *name );
extern int searchName( char *name );

extern int addCharConst(char c);
extern int addIntConst(int n);
extern int addStringConst(char *s);

extern char getCharConst(int n);
extern int getIntConst(int n);
extern char *getStringConst(int n);

extern t_token nextToken(void);

char nextChar;

t_token token;
int tokenSecundario;

#endif