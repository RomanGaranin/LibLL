/*
	Roman Garanin

*/
#ifndef NODE_H
#define NODE_H
#include "stdint.h"

typedef struct node NODE;

void Node_Add(NODE** List, NODE* node);
void Node_Del(NODE** List, NODE* node);
void Node_Del_First(NODE** List, NODE* node);







#endif // !NODE_H

