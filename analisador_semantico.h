
#ifndef _SEMANCTIC_ANALYSIS_H_
#define _SEMANCTIC_ANALYSIS_H_

#include "analisador_sintatico.h"
#include "analisador_lexico.h"
#include "alerta_erro.h"



#define INTEGER_SIZE 1
#define CHAR_SIZE 1
#define BOOLEAN_SIZE 1
#define STRING_SIZE 1
#define UNIVERSAL_SIZE 0

#define true 1
#define false 0

#define IS_TYPE_KIND(k)    ((k)==ARRAY_TYPE_ || \
							(k)==STRUCT_TYPE_|| \
							(k)==ALIAS_TYPE_ || \
							(k)==SCALAR_TYPE_)

#define NO_KIND_DEF_ -1 
#define	VAR_  0
#define	PARAM_ 1
#define	FUNCTION_ 2 
#define	FIELD_ 3
#define	ARRAY_TYPE_ 4
#define	STRUCT_TYPE_ 5
#define	ALIAS_TYPE_ 6
#define	SCALAR_TYPE_ 7
#define	UNIVERSAL_ 8

/*
typedef enum {  NO_KIND_DEF_=-1, 
				VAR_, 
				PARAM_, 
				FUNCTION_, 
				FIELD_,
				ARRAY_TYPE_,
				STRUCT_TYPE_,
				ALIAS_TYPE_,
				SCALAR_TYPE_,
				UNIVERSAL_
			} t_kind;
*/

typedef struct {
	int nName;
	int	eKind;
	struct object *pNext;
	struct object *pPrev;
	
	union{

		struct {
			int nIndex;
			int nSize;
			struct  object * pType;
		} Var, Param, Field;

		struct {
			struct object * pRetType;
			struct object * pParams;
			int nIndex;
			int nParam;
			int nVars;
		} Function;

		struct {
			int nSize;
			struct object *pElemType;
			int 	nNumElems;
		} Array;

		struct {
			int nSize;
			struct object *pFields;
		} Struct;

		struct {
			int nSize;
			struct object *pBaseType;
		} Alias , Type;
	}_;

} object , *pobject;





//preenchido com os seguintes campos
//{ nName , eKind , pNext ,pPrev , _.Type.nSize }

static object int_= { -1, SCALAR_TYPE_ , NULL,NULL, INTEGER_SIZE};
static object * pInteger = &int_;


static object char_ = { -1 ,SCALAR_TYPE_ , NULL,NULL, CHAR_SIZE};
static object * pChar = &char_;

static object bool_ = { -1, SCALAR_TYPE_ , NULL,NULL, BOOLEAN_SIZE};
static object * pBool = &bool_;

static object string_ = { -1, SCALAR_TYPE_ , NULL,NULL, STRING_SIZE};
static object * pString = &string_;

static object universal_= { -1, SCALAR_TYPE_ , NULL,NULL,UNIVERSAL_SIZE};
static object * pUniversal = &universal_;


typedef struct attr{

	union{

		struct{
			object * obj;
			int name;		
		}ID,IDU,IDD;

		struct {
			object * type;
			int nSize;
		} T, LV,F,Z,R,L,E;

		struct {
			object * list;
			int nSize;
		} LI , DC ,LP;

		struct {
			object * type;
			int pos;
			int val;
		} FALSE, TRUE, NUM;

		struct {
			object * type;
			int pos;
			char val;
		} CHR;

		struct {
			object * type;
			int pos;
			char * val;
		} STR;

		struct 
		{
			object * type;
			object * param;
			int err;
			int n;	
		}MC,LE;

		struct 
		{
			int offset;
		}MF;

		struct 
		{
			int label;
		}MT, ME, MW;

	}_;

}t_attrib;




typedef enum{
	r_P0, 	//P -> LDE

	r_LDE0,	//LDE -> LDE DE
	r_LDE1,	//LDE -> DE

	r_DE0,	//DE -> DF
	r_DE1,	//DE -> DT
	r_DE2,	//DE -> DV

	r_T0,	//T -> integer
	r_T1,	//T -> char
	r_T2,	//T -> boolean
	r_T3,	//T -> string
	r_T4,	//T -> IDU

	r_DT0,	//DT -> type IDD = array [ NUM ] of T ;
	r_DT1,	//DT -> type IDD = struct NB { DC } ;
	r_DT2,	//DT -> type IDD = T ;

	r_DC0,	//DC -> DC ; LI : T
	r_DC1,	//DC -> LI : T

	r_DF0,	//DF -> function IDD NF ( LP ) : T  MF B

	r_LP0,	//LP -> LP , IDD : T
	r_LP1,	//LP -> IDD : T

	r_B0,	//B -> { LDV LS }
	r_B1,	//B -> { LS }

	r_LDV0,	//LDV -> LDV DV
	r_LDV1,	//LDV -> DV

	r_LS0,	//LS -> LS S
	r_LS1,	//LS -> S

	r_DV0,	//DV -> var LI : T ;

	r_LI0,	//LI -> LI , IDD
	r_LI1,	//LI -> IDD

	r_S0,	//S -> if ( E ) MT S
	r_S1,	//S -> if ( E ) MT S else ME S 
	r_S2,	//S -> while MW ( E ) MT S 
	r_S3,	//S -> do MW S while ( E ) ;
	r_S4,	//S -> NB B
	r_S5,	//S -> E ;
	r_S6,	//S -> break ;
	r_S7,	//S -> continue ;
	r_S8,	//S -> return E ;

	r_E0,	//E -> E && L
	r_E1,	//E -> E || L
	r_E2,	//E -> L

	r_L0,	//L -> L < R
	r_L1,	//L -> L > R
	r_L2,	//L -> L <= R
	r_L3,	//L -> L >= R
	r_L4,	//L -> L == R
	r_L5,	//L -> L != R
	r_L6,	//L -> R

	r_R0,	//R -> R + Z
	r_R1,	//R -> R - Z
	r_R2,	//R -> Z

	r_Z0,	//Z -> Z * F
	r_Z1,	//Z -> Z / F
	r_Z2,	//Z -> F

	r_F0,	//F -> LV
	r_F1,	//F -> ++ LV
	r_F2,	//F -> -- LV
	r_F3,	//F -> LV ++
	r_F4,	//F -> LV --
	r_F5,	//F -> LV MA = E
	r_F6,	//F -> IDU MC ( LE )
	r_F7,	//F -> - F
	r_F8,	//F -> ! F
	r_F9,	//F -> TRUE
	r_F10,	//F -> FALSE
	r_F11,	//F -> CHR
	r_F12,	//F -> STR
	r_F13,	//F -> NUM

	r_LE0,	//LE -> LE , E
	r_LE1,	//LE -> E

	r_LV0,	//LV -> LV . ID
	r_LV1,	//LV -> LV [ E ]
	r_LV2,	//LV -> IDU

	r_IDD0,	//IDD -> id
	r_IDU0,	//IDU -> id
	r_ID0,	//ID -> id

	r_TRUE0,	//TRUE -> true
	r_FALSE0,	//FALSE -> false
	r_CHR0,	//CHR -> chr
	r_STR0,	//STR -> str
	r_NUM0,	//NUM -> num

	r_NB0,	//NB -> ''

	r_NF0,	//NF -> ''

	r_MF0,	//MF -> ''

	r_MC0,	//MC -> ''

	r_MT0,	//MT -> ''

	r_ME0,	//ME -> ''

	r_MW0,	//MW -> ''

	r_MA0	//MA -> ''

} t_rule;


extern int CheckTypes(object *t1, object * t2);
extern int PushSem(t_attrib attrib);
extern int PopSem();
extern t_attrib TopSem(int offFromTop);
extern int newLabel();
extern int init_out_file(char * filename);

extern void Semantics(int rule);




















#endif