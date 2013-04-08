#ifndef STACK_QUEUE_H
#define STACK_QUEUE_H

struct Node_int{
	int datum;
	Node_int *link;
};

int Size(Node_int *);

#endif