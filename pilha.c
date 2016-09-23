#ifndef _PILHA_C_
#define _PILHA_C_

#include "pilha.h"

void show_stack(){
   int i;
   for(i=0;i<=top;i++)
      printf("%d ",stack[i]);
   printf("\n");
}

int isempty() {

   if(top == -1)
      return 1;
   else
      return 0;
}
   
int isfull() {

   if(top == STACK_MAX_SIZE)
      return 1;
   else
      return 0;
}

int Top() {
   return stack[top];
}


void Pop(int num) {
   int data;
	
   if(!isempty()) {
      data = stack[top];
      top = top - num;  
   }
}

void Push(int data) {

   if(!isfull()) {
      top = top + 1;   
      stack[top] = data;
   }  
}

#endif