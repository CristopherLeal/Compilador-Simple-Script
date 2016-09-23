#ifndef _PILHA_H_
#define _PILHA_H_

#define STACK_MAX_SIZE 1000

static int stack[STACK_MAX_SIZE];     
static int top = -1;            

extern void show_stack();
extern int isempty();
extern int isfull();
extern int Top();
extern void Pop(int num);
extern void Push(int data);

#endif