#ifndef MY_STACK_H
#define MY_STACK_H
#include"stack_queue.h"


void Push(Node_int *&, int);
int Pop(Node_int *&);
int OnTop(Node_int *);
void Clear(Node_int *&, int = -1);

#endif