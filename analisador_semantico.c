#ifndef _SEMANCTIC_ANALYSIS_C_
#define _SEMANCTIC_ANALYSIS_C_

#include "analisador_semantico.h"


#define STACK_SEM_MAX_SIZE 1000

static t_attrib StackSem[STACK_SEM_MAX_SIZE];     
static int topSem = -1;  
static  int first_block_init =0;    

int isemptysem() {

   if(topSem == -1)
      return 1;
   else
      return 0;
}
   
int isfullsem() {

   if(topSem == STACK_SEM_MAX_SIZE)
      return 1;
   else
      return 0;
}

t_attrib TopSem(int offFromTop) {
   return StackSem[topSem - offFromTop];
}


int PopSem() {
  	
   if(!isemptysem()) {
      topSem = topSem - 1;
      return 1;  
   }
   return 0;
}

int PushSem(t_attrib data) {

   if(!isfullsem()) {
      topSem = topSem + 1;   
      StackSem[topSem] = data;
      /*
      printf("%s\n","Push" );
      printf("%d\n", data.nName);
      printf("%d\n", data.eKind);*/
      return 1;
   }  
   return 0;
}

void show_stack_sem(){
 /*  	int i;
   	printf("%s\n","_________________________________________" );
   	for(i=0;i< topSem;i++)
       printf(" %d.%d.%d.%d.%d.%d.%d.%d \n", StackSem[i]);
   	printf("%s\n","_________________________________________" );
   	*/
   	printf("Stack %d\n", topSem );
   	printf("s7 %d\n",StackSem[7]._.MC.err );
}


 










void Semantics(int rule){
 
	printf("%s\n", "semantico");
    t_attrib IDD, IDU, ID, T , LI, LI0, LI1 , LV, LV1, LV0, LE, LE1, LE0, DC,DC0, DC1,LP, F, F1,F0,
    		 Z, Z1, Z0, R, R1, R0, L, L0, L1, E, E1, E0, TRUE0, FALSE0, CHR, STR, NUM,
    		 MC, MT, MW, ME,NB ; 
	int name;
	int nParam;
	object * p, *q;
	object * t, *t1, *t2;
	object * n;
	object  * f;

	
	if(!first_block_init){
		NewBlock();
		first_block_init=1;
	}

	show_stack_sem();

	switch(rule){

		
		case r_T0 :	//T -> integer
			T._.T.type = pInteger;
			PushSem(T);
			break;
		case r_T1 :	//T -> char
			T._.T.type = pChar;
			PushSem(T);
			break;
		case r_T2 :	//T -> boolean
			T._.T.type = pBool;
			PushSem(T);
			break;
		case r_T3 :	//T -> string
			T._.T.type = pString;
			PushSem(T);
			break;
		case r_T4 :	//T -> IDU 
			printf("%s\n","r_T4");
			IDU = TopSem(0);
			PopSem();
			p = IDU._.IDU.obj;
			//printf("KIND %s\n",p->eKind );
			if( IS_TYPE_KIND(p->eKind) || p->eKind == UNIVERSAL_ )
				T._.T.type = p;
			else{
				T._.T.type = pUniversal;
				Error(ERR_TYPE_EXPECTED);
			}
			PushSem(T);		
			break;



		case r_LI0 :	//LI -> LI , IDD
			printf("%s\n","r_LI0");

			IDD = TopSem(0);
			PopSem();
			LI1 = TopSem(0);
			PopSem();
			LI0._.LI.list = IDD._.IDD.obj;
			printf("idd name %d\n",LI0._.LI.list->nName );
			PushSem(LI0); 
			break;

		case r_LI1 :	//LI -> IDD
			printf("%s\n","r_LI1");
			IDD = TopSem(0);
			printf("idd name %d\n",IDD._.IDD.obj->nName );
			PopSem();
			LI._.LI.list = IDD._.IDD.obj;
			PushSem(LI);
			break;

		case r_DV0 :  //DV -> var LI : T ;
			printf("%s\n","r_DV0");
			show_level();
			T = TopSem(0);
			PopSem();
			LI = TopSem(0);
			PopSem();
			p = LI._.LI.list;
			t = T._.T.type;
			while( p != NULL && p->eKind == NO_KIND_DEF_ ){
			//	printf("-------var name ----- %d\n",p->nName );
				p->eKind = VAR_;
				p->_.Var.pType = t;
				p = p->pNext;
			}

			break;		

	

		case r_DC0 :	//DC -> DC ; LI : T

			printf("%s\n", "r_DC0");
			//show_level();
			T = TopSem(0);
			PopSem();
			LI = TopSem(0);
			PopSem();
			DC = TopSem(0);
			PopSem();
			p = LI._.LI.list;
			t = T._.T.type;
			while( p != NULL && p->eKind == NO_KIND_DEF_ ){
			//	printf(" ---- field name -- %d\n",p->nName );
				p->eKind = FIELD_;
				p->_.Field.pType = t;
			//	printf("KIND%d\n",p->eKind );
				p = p->pNext;

			}
			DC._.DC.list = LI._.LI.list;
		
			PushSem(DC); 
			break;

		case r_DC1 :	//DC -> LI : T
			printf("%s\n", "r_DC1");
			//show_level();
			T = TopSem(0);
			PopSem();
			LI = TopSem(0);
			PopSem();
			p = LI._.LI.list;
			t = T._.T.type;
			while( p != NULL && p->eKind == NO_KIND_DEF_ ){
			//	printf(" ---- field name -- %d\n",p->nName );
				p->eKind = FIELD_;
				p->_.Field.pType = t;
			//	printf("KIND%d\n",p->eKind );
				p = p->pNext;

			}
			DC._.DC.list = LI._.LI.list;
		
			PushSem(DC); 
			break;
		

		case r_LP0 :	//LP -> LP , IDD : T

			printf("%s\n", "r_LP0");
			T = TopSem(0);
			PopSem();
			IDD = TopSem(0);
			PopSem();
			LP = TopSem(0);
			PopSem();
			p = IDD._.IDD.obj;
			t = T._.T.type;
			p->eKind = PARAM_;
			p->_.Param.pType = t;
			LP._.LP.list = p;
			PushSem(LP);

			break;
		case r_LP1 :	//LP -> IDD : T

			printf("%s\n", "r_LP1");
			T = TopSem(0);
			PopSem();
			IDD = TopSem(0);
			PopSem();
			p = IDD._.IDD.obj;
			t = T._.T.type;
			p->eKind = PARAM_;
			p->_.Param.pType = t;
			LP._.LP.list = p;
			PushSem(LP);
			break;

		case r_MF0 :	//MF -> ''	

			T = TopSem(0);
			LP = TopSem(1);
			IDD = TopSem(2);
			f = IDD._.IDD.obj;
			f->eKind = FUNCTION_;
			f->_.Function.pRetType = T._.T.type;
			f->_.Function.pParams = LP._.LP.list;
			p=LP._.LP.list;
			while(p!=NULL && p->eKind == PARAM_ ){
				printf(" ------ parametro  -----------\n" );
				p = p->pNext;
			}
			break;

		case r_DF0 : // DF -> function IDD NF ( LP ) : T MF B

				EndBlock();
				break;


		case r_DT0 :	//DT -> type IDD = array [ NUM ] of T ;	

				T = TopSem(0);
				PopSem();
				NUM = TopSem(0);
				PopSem();
				IDD = TopSem(0);
				PopSem();

				p = IDD._.IDD.obj;
				n = NUM._.NUM.val;
				t = T._.T.type;

				p->eKind = ARRAY_TYPE_;
				p->_.Array.nNumElems = n;
				p->_.Array.pElemType = t;
				break;

		case r_DT1 : //DT -> type IDD = struct NB { DC }

				printf("%s\n","r_DT1" );
				DC = TopSem(0);
				PopSem();
				IDD = TopSem(0);
				PopSem();
				p = IDD._.IDD.obj;
				p->eKind = STRUCT_TYPE_;
				p->_.Struct.pFields = DC._.DC.list;

				EndBlock();
				break;	

		case r_DT2 :	//DT -> type IDD = T ;
				
				T = TopSem(0);
				PopSem();
				t = T._.T.type;
				IDD = TopSem(0);
				PopSem();
				p = IDD._.IDD.obj;

				p->eKind = ALIAS_TYPE_;
				p->_.Alias.pBaseType = t;

				break;

			

		case r_IDD0: //IDD -> id
				printf("%s\n", "r_IDD0");
				name = tokenSecundario;
				IDD._.IDD.name= name; 

				if( (p = Search(name)) != NULL){
					Error(ERR_REDECL);
				}else
				{
					p = Define(name);
					printf("*****\ndefiniu %d\n",name);
				}
				IDD._.IDD.obj = p;
				p->eKind = NO_KIND_DEF_;
				PushSem(IDD);
				break;
			
		case r_IDU0: //IDU ->id
				printf("%s\n","r_IDU0" );
				name = tokenSecundario;
				IDU._.IDU.name = name;

				if((p = Find(name)) == NULL){
					printf("*****\nusou %d\n",name);
					Error(ERR_NOT_DECL);
				}

				IDU._.IDU.obj = p;
				printf("-----------------***%d***------------------\n", p->eKind);
				PushSem(IDU);

			break;


			
		case r_ID0 : //ID -> id

			name = tokenSecundario;
			IDU._.IDU.name = name;
			PushSem(IDU);

			break;



		case r_E0 :	//E -> E && L

			L = TopSem(0);
			PopSem();
			E1 = TopSem(0);
			PopSem();
			if(!CheckTypes(L._.L.type, pBool))
				Error(ERR_BOOL_TYPE_EXPECTED);
			if(!CheckTypes(E1._.E.type, pBool))
				Error(ERR_BOOL_TYPE_EXPECTED);
			E0._.E.type = pBool;
			PushSem(E0);
			break;			

		case r_E1 :	//E -> E || L

			L = TopSem(0);
			PopSem();
			E1 = TopSem(0);
			PopSem();
			if(!CheckTypes(L._.L.type, pBool))
				Error(ERR_BOOL_TYPE_EXPECTED);
			if(!CheckTypes(E1._.E.type, pBool))
				Error(ERR_BOOL_TYPE_EXPECTED);
			E0._.E.type = pBool;
			PushSem(E0);
			break;			

		case r_E2 :	//E -> L	
			printf("%s\n","r_E2" );
			L = TopSem(0);
			PopSem();
			E._.E.type = L._.L.type;
			PushSem(E);
			break;	




		case r_LV0 :	//LV -> LV . ID
			ID = TopSem(0);
			PopSem();
			LV1 =TopSem(0);
			PopSem();
			t = LV1._.LV.type;
			if( t->eKind != STRUCT_TYPE_ ){
				if( t->eKind != UNIVERSAL_ )
					Error( ERR_KIND_NOT_STRUCT );
				LV0._.LV.type = pUniversal;
			}else{
				p = t->_.Struct.pFields;
				while( p!= NULL ){
					if( p->nName == ID._.ID.name )
						break;	
					p = p->pNext;
				}	

				if( p == NULL ){
					Error( ERR_FIELD_NOT_DECL );
					LV0._.LV.type = pUniversal;
				}
				else{
					LV0._.LV.type = p->_.Field.pType;
				}
			}	
			PushSem(LV0);
			break;

		case r_LV1 :	//LV -> LV [ E ]

			E = TopSem(0);
			PopSem();
			LV1 = TopSem(0);
			PopSem();
			t = LV1._.LV.type;
			if( t == pString ){
				LV0._.LV.type = pChar;
			}
			else
				if( t->eKind != ARRAY_TYPE_ ){
					if( t->eKind != UNIVERSAL_ )
						Error( ERR_KIND_NOT_ARRAY );
					LV0._.LV.type = pUniversal;
				}
				else{
					LV0._.LV.type = t->_.Array.pElemType;
				}
			if( !CheckTypes( E._.E.type, pInteger ) ){
				Error( ERR_INVALID_INDEX_TYPE );
			}
			PushSem(LV0);
			break;



		case r_LV2 :	//LV -> IDU	

			printf("%s\n","r_LV2");
			IDU  = TopSem(0);
			PopSem();
			p = IDU._.IDU.obj;
			if( p->eKind != VAR_ && p->eKind != PARAM_ ){
				if( p->eKind != UNIVERSAL_ )
					Error( ERR_KIND_NOT_VAR );
				LV._.LV.type = pUniversal;
			}else{			
				LV._.LV.type = p->_.Var.pType;
			}
			PushSem(LV);
			break;



		case r_S0 :	//S -> if ( E ) MT S

			MT = TopSem(0);
			PopSem();
			E = TopSem(0);
			PopSem();
			t = E._.E.type;
			if( !CheckTypes(t, pBool) )
				Error( ERR_BOOL_TYPE_EXPECTED);
			break;

		case r_S1 :	//S -> if ( E ) MT S else ME S

			ME = TopSem(0);
			PopSem();
			MT = TopSem(0);
			PopSem();
			E = TopSem(0);
			PopSem();
			t = E._.E.type;
			if( !CheckTypes(t, pBool) )
				Error( ERR_BOOL_TYPE_EXPECTED);
			break; 

		case r_S2 : //S -> while MW ( E ) MT S

			MT = TopSem(0);
			PopSem();
			E = TopSem(0);
			PopSem();
			MW = TopSem(0);
			PopSem();
			t = E._.E.type;
			if( !CheckTypes(t, pBool) )
				Error( ERR_BOOL_TYPE_EXPECTED);			
			break; 

		case r_S3 :	//S -> do MW S while ( E ) ;

			E = TopSem(0);
			PopSem();
			MW = TopSem(0);
			PopSem();	
			t = E._.E.type;
			if( !CheckTypes(t, pBool) )
				Error( ERR_BOOL_TYPE_EXPECTED);	
			break;

		case r_S4:  //S -> NB B
		
				EndBlock();
				break;
					
		case r_S5 :	//S -> E ;

			E = TopSem(0);
			PopSem();
			break;

		case r_S6 :	//S -> break ;
			break;
		case r_S7 :	//S -> continue ;
			break;
		case r_S8 :	//S -> return E ;
			break;



		case r_L0 :	//L -> L < R
			
			R = TopSem(0);
			PopSem();
			L1 = TopSem(0);
			PopSem();
			if(!CheckTypes(R._.R.type, L1._.L.type))
				Error(ERR_TYPE_MISMATCH);
			L0._.L.type = pBool;
			PushSem(L0);
			break;

		case r_L1 :	//L -> L > R
			
			R = TopSem(0);
			PopSem();
			L1 = TopSem(0);
			PopSem();
			if(!CheckTypes(R._.R.type, L1._.L.type))
				Error(ERR_TYPE_MISMATCH);
			L0._.L.type = pBool;
			PushSem(L0);
			break;

		case r_L2 :	//L -> L <= R
			
			R = TopSem(0);
			PopSem();
			L1 = TopSem(0);
			PopSem();
			if(!CheckTypes(R._.R.type, L1._.L.type))
				Error(ERR_TYPE_MISMATCH);
			L0._.L.type = pBool;
			PushSem(L0);
			break;

		case r_L3 :	//L -> L >= R

			R = TopSem(0);
			PopSem();
			L1 = TopSem(0);
			PopSem();
			if(!CheckTypes(R._.R.type, L1._.L.type))
				Error(ERR_TYPE_MISMATCH);
			L0._.L.type = pBool;
			PushSem(L0);
			break;

		case r_L4 :	//L -> L == R

			R = TopSem(0);
			PopSem();
			L1 = TopSem(0);
			PopSem();
			if(!CheckTypes(R._.R.type, L1._.L.type))
				Error(ERR_TYPE_MISMATCH);
			L0._.L.type = pBool;
			PushSem(L0);
			break;

		case r_L5 :	//L -> L != R

			R = TopSem(0);
			PopSem();
			L1 = TopSem(0);
			PopSem();
			if(!CheckTypes(R._.R.type, L1._.L.type))
				Error(ERR_TYPE_MISMATCH);
			L0._.L.type = pBool;
			PushSem(L0);
			break;

		case r_L6 :	//L -> R
			printf("%s\n","r_L6" );	
			R = TopSem(0);
			PopSem();
			L._.L.type = R._.R.type;
			PushSem(L);
			break;	





		case r_R0 :	//R -> R + Z

			Z = TopSem(0);
			PopSem();
			R1 = TopSem(0);
			PopSem();
			if(!CheckTypes(Z._.Z.type, R1._.R.type))
				Error(ERR_TYPE_MISMATCH);
			if(!CheckTypes(R1._.R.type, pInteger))
				Error(ERR_INVALID_TYPE);
			R0._.R.type = R1._.R.type;
			PushSem(R0);
			break;

		case r_R1 :	//R -> R - Z

			Z = TopSem(0);
			PopSem();
			R1 = TopSem(0);
			PopSem();
			if(!CheckTypes(Z._.Z.type, R1._.R.type))
				Error(ERR_TYPE_MISMATCH);
			if(!CheckTypes(R1._.R.type, pInteger))
				Error(ERR_INVALID_TYPE);
			R0._.R.type = R1._.R.type;
			PushSem(R0);
			break;

		case r_R2 :	//R -> Z
			printf("%s\n","r_R2");
			Z = TopSem(0);
			PopSem();
			R._.R.type = Z._.Z.type;
			PushSem(Z);
			break;	
			


		case r_Z0 :	//Z -> Z * F

			printf("%s\n","r_Z0" );
			F = TopSem(0);
			PopSem();
			Z1 = TopSem(0);
			PopSem();
			if(!CheckTypes(F._.F.type, Z1._.Z.type))
				Error(ERR_TYPE_MISMATCH);
			if(!CheckTypes(Z1._.Z.type, pInteger))
				Error(ERR_INVALID_TYPE);
			PushSem(Z1);
			break;	

		case r_Z1 :	//Z -> Z / F

			printf("%s\n","r_Z1" );
			F = TopSem(0);
			PopSem();
			Z1 = TopSem(0);
			PopSem();
			if(!CheckTypes(F._.F.type, Z1._.Z.type))
				Error(ERR_TYPE_MISMATCH);
			if(!CheckTypes(Z1._.Z.type, pInteger))
				Error(ERR_INVALID_TYPE);
			PushSem(Z1);
			break;

		case r_Z2 :	//Z -> F

			printf("%s\n", " r_Z2");
			F = TopSem(0);
			PopSem();
			Z._.Z.type = F._.F.type;
			PushSem(Z);
			break;	





		case r_F0:	//F -> LV
			printf("%s\n", "r_F0");
			LV = TopSem(0);
			PopSem();
			F._.F.type = LV._.LV.type;
			PushSem(F);
			break;

		case r_F1:	//F -> ++ LV
			LV = TopSem(0);
			PopSem();
			t = LV._.LV.type;
			if( ! CheckTypes(t,pInteger))
				Error(ERR_INVALID_TYPE);
			F._.F.type = pInteger; 
			PushSem(F);
			break;	

		case r_F2:	//F -> -- LV

			LV = TopSem(0);
			PopSem();
			t = LV._.LV.type;
			if( ! CheckTypes(t,pInteger))
				Error(ERR_INVALID_TYPE);
			F._.F.type = pInteger; 
			PushSem(F);
			break;

		case r_F3:	//F -> LV ++

			LV = TopSem(0);
			PopSem();
			t = LV._.LV.type;
			if( ! CheckTypes(t,pInteger))
				Error(ERR_INVALID_TYPE);
			F._.F.type = pInteger; 
			PushSem(F);
			break;

		case r_F4:	//F -> LV --

			LV = TopSem(0);
			PopSem();
			t = LV._.LV.type;
			if( ! CheckTypes(t,pInteger))
				Error(ERR_INVALID_TYPE);
			F._.F.type = pInteger; 
			PushSem(F);
			break;

		case r_F5:	//F -> LV MA = E
		
			E = TopSem(0);
			PopSem();
			LV = TopSem(0);
			PopSem();
			t1 = LV._.LV.type;
			t2 = E._.E.type;
			if( ! CheckTypes( t1, t2 ) )
				Error( ERR_TYPE_MISMATCH );
			F._.F.type = t2;
			PushSem(F);
			break;

		case r_F6:	//F -> IDU MC ( LE )
				printf("%s","F -> IDU MC ( LE )");
				LE = TopSem(0);
				PopSem();
				MC = TopSem(0);
				PopSem();
				IDU = TopSem(0);
				PopSem();
				F._.F.type = MC._.MC.type;
				if(!MC._.MC.err){
					if( LE._.LE.param != NULL && LE._.LE.param->eKind == PARAM_)
						Error(ERR_TOO_FEW_ARGS);
				}
				PushSem(F);
				break;


		case r_F7:	//F -> - F

			F1 = TopSem(0);
			PopSem();
			t=F1._.F.type;
			if(!CheckTypes(t,pInteger))
				Error(ERR_INVALID_TYPE);
			F0._.F.type = pInteger;
			PushSem(F0);
			break;
				
		case r_F8:	//F -> ! F

			F1 = TopSem(0);
			PopSem();
			t=F1._.F.type;
			if(!CheckTypes(t,pBool))
				Error(ERR_INVALID_TYPE);
			F0._.F.type = pBool;
			PushSem(F0);
			break;

		case r_F9:	//F -> TRUE

			TRUE0 = TopSem(0);
			PopSem();
			F._.F.type = pBool;
			PushSem(F);
			break;

		case r_F10:	//F -> FALSE

			FALSE0 = TopSem(0);
			PopSem();
			F._.F.type = pBool;
			PushSem(F);
			break;

		case r_F11:	//F -> CHR

			CHR = TopSem(0);
			PopSem();
			F._.F.type = pChar;
			PushSem(F);
			break;

		case r_F12:	//F -> STR

			STR = TopSem(0);
			PopSem();
			F._.F.type = pString;
			PushSem(F);
			break;

		case r_F13:	//F -> NUM

			NUM = TopSem(0);
			PopSem();
			F._.F.type = pInteger;
			PushSem(F);
			break;

	

		case r_LE0 :	//LE -> LE , E

			printf("%s\n"," ++++++++++++++++ r_LE0 ++++++++++++++++++");	
			E = TopSem(0);
			PopSem();
			LE1 = TopSem(0);
			PopSem();
			LE0._.LE.param = NULL;
			LE0._.LE.err = LE1._.LE.err;
			nParam = LE1._.LE.n;
			if( !LE1._.LE.err )
			{
				p = LE1._.LE.param;
				if( p == NULL || p->eKind != PARAM_){
					Error(ERR_TOO_MANY_ARGS);
					LE0._.LE.err = true;
				}
				else
				{
					if( !CheckTypes(p->_.Param.pType,E._.E.type ) ){
						Error( ERR_PARAM_TYPE);
					}
				}
				LE0._.LE.param = p->pPrev;
				LE0._.LE.n = nParam+1;
			}
			PushSem(LE0);	
		
			break;
		case r_LE1 :	//LE -> E	

			printf(" !!!!!!!!!!!!!!!!!!!!!!!!!! %s\n","r_LE1");	
			E = TopSem(0);
			PopSem();
			MC = TopSem(0);
			printf("%d\n", MC._.MC.err);
			LE._.LE.param = NULL;
			LE._.LE.err = MC._.MC.err;
			nParam = 1;
			if( !MC._.MC.err )
			{
				printf("%s\n"," ---------------entrou +++++++++++++++++++" );	
				p = MC._.MC.param;
				if( p == NULL || p->eKind != PARAM_){
					Error(ERR_TOO_MANY_ARGS);
					LE._.LE.err = true;
				}
				else
				{
					if( !CheckTypes(p->_.Param.pType,E._.E.type ) ){
						Error( ERR_PARAM_TYPE);
					}
				}
				LE._.LE.param = p->pPrev;
				LE._.LE.n = nParam+1;
			}
			PushSem(LE);	

			break;



		case r_NB0: // NB -> ''

			printf("%s\n","r_NB0" );
			NewBlock();
			break;	

		case r_NF0: //NF -> ''
		
			NewBlock();
			break;	

		case r_MC0 :	//MC -> ''	

			printf("%s\n","r_MC0" );
			IDU = TopSem(0);
			f = IDU._.IDU.obj;
			if( f->eKind != FUNCTION_ ){
				Error( ERR_KIND_NOT_FUNC );
				MC._.MC.type = pUniversal;
				MC._.MC.param = NULL;
				MC._.MC.err = true;
			}
			else
			{
				MC._.MC.type = f->_.Function.pRetType;
				p = f->_.Function.pParams;
			
				//navegar até o ultimo parametro
				while(p->pNext != NULL){
					p = p->pNext;
				}

				MC._.MC.param = p;
				MC._.MC.err = false;
				printf("%s\n","err = false" );
				printf("%d\n",MC._.MC.err );
			}
			PushSem(MC);
			break;

		case r_MT0 :	//MT -> ''

			PushSem(MT);
			break;

		case r_ME0 : //ME -> ''

			PushSem(ME);
			break;

		case r_MW0 :	//MW -> ''	

			PushSem(MW);
			break;



		case r_TRUE0 :

			TRUE0._.TRUE.type = pBool;
			TRUE0._.TRUE.val = true;
			PushSem(TRUE0);
			break;

		case r_FALSE0 :

			FALSE0._.FALSE.type = pBool;
			FALSE0._.FALSE.val = false;
			PushSem(FALSE0);
			break;

		case r_CHR0 :	//CHR -> chr

			CHR._.CHR.type = pChar;
			CHR._.CHR.pos = tokenSecundario;
			CHR._.CHR.val = getCharConst(CHR._.CHR.pos);
			PushSem(CHR);
			break;

		case r_STR0 :   //STR -> str

			STR._.STR.type = pString;
			STR._.STR.pos = tokenSecundario;	
			STR._.STR.val = getStringConst(STR._.STR.pos);
			PushSem(STR);
			break;

		case r_NUM0 :	//NUM -> num

			NUM._.NUM.type = pInteger;
			NUM._.NUM.pos = tokenSecundario;
			NUM._.NUM.val = getIntConst(NUM._.NUM.pos);
			PushSem(NUM);
			break;
	
						
	}
}



#endif



int CheckTypes(object * t1, object * t2)
{
	
	if( t1 == t2 )
		return true;	
	else if( t1 == pUniversal || t2 == pUniversal )
		return true;
	else if( t1->eKind == UNIVERSAL_ || t2->eKind == UNIVERSAL_ )
		return true;
	else
		return false;
	
	return true;	
}






