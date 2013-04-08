#include "my_stack.h"
#include <iostream>

void Push(Node_int *&top, int data){
	 Node_int *p = NULL;
	 p = new Node_int;
	 p->datum = data;
	 p->link = top;
	 top = p;
}

int Pop(Node_int *&top){
	if(top != NULL){
		Node_int *p = NULL;
		int date;
		p = top;
		date = p->datum;
		p->datum = 0;
		top = p->link;
		delete p;
		return date;
	}
	else return -1;
}

void Clear(Node_int *&top, int size){
	Node_int *p = NULL;
	for(;top != NULL && size != 0; size--){
		p = top;
		top = top->link;
		p->datum = 0;
		delete p;
	}
}

int OnTop(Node_int *top){
	if(top != NULL) return top->datum;
	else return -1;
}