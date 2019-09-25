/*
	Roman Garanin

*/
#ifndef NODE_H
#define NODE_H
#include "stdint.h"
#include "stdlib.h"
#include "stdbool.h"
#include "stdarg.h"
#include "stdio.h"

typedef struct _node
{
	struct _node* next;
	struct _node* prev;
	uint16_t ID;
}NODE;


void Node_Init_Stub(NODE* stub);

void Node_Connect_to_Stub(NODE** node, NODE* stub);


void Node_Connect(NODE** List,  NODE* node);
void Node_Disconnect(NODE** List, NODE* node);
void Node_Disconnect_First(NODE** List, NODE** deleted_node);
void Node_Change_List(NODE** SrcList, NODE** DestList, NODE* node);
void Node_Clear_List(NODE** List);

NODE* NodeFind(NODE* List, bool (*pCheckSign)(void* obj, va_list args), ...);









#endif // !NODE_H

