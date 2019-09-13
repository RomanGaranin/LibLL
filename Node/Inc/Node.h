/*
	Roman Garanin

*/
#ifndef NODE_H
#define NODE_H
#include "stdint.h"
#include "stdlib.h"


typedef struct _node
{
	uint16_t ID;
	struct _node* next;
	struct _node* prev;
}NODE;
extern NODE* NodeStub;
void Node_Add(NODE** List,  NODE* node);
void Node_Del(NODE** List, NODE* node);
void Node_Del_First(NODE** List, NODE** deleted_node);
void Node_Change_List(NODE** SrcList, NODE** DestList, NODE* node);
void Node_Clear_List(NODE** List);







#endif // !NODE_H

