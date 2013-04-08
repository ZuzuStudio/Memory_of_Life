#include"stack_queue.h"
#include<iostream>

int Size(Node_int *end){
	int size = 0;
	Node_int *p = end;
	while(p != NULL){
		size++;
		p = p->link;
	}
	return size;
}

bool isEmpty(Node_int *end){
	return end ? 1 : 0;
}