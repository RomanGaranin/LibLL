/*
	Roman Garanin
*/
#ifndef NODE_H
#define NODE_H
#define _CRT_SECURE_NO_WARNINGS

#ifdef __cplusplus
extern "C" {
#endif

#include "stdint.h"
#include "stdlib.h"
#include "stdbool.h"
#include "stdarg.h"
#include "stdio.h"
#include "string.h"

	typedef struct _node
	{
		struct _node* next;
		struct _node* prev;
		uint16_t ID;
	}NODE;

	enum dir
	{
		Next = 0,
		Prev
	};
	extern  NODE* Stub;

	void Node_Init_Stub(NODE* stub);
	void Node_Connect_to_Stub(NODE** node, NODE* stub);

	void Node_Connect(NODE** List, NODE* node, NODE** iterator);

	void Node_Disconnect(NODE** List, NODE* node, NODE** iterator);
	void Node_Disconnect_First(NODE** List, NODE** deleted_node);

	void Node_Change_List(NODE** SrcList,
		NODE** DestList,
		NODE* node,
		NODE** sl_iterator,
		NODE** dl_iterator);

	void Node_Clear_List(NODE** List);

	NODE* NodeFind(NODE* start_node, enum dir direction, bool (*pCheckSign)(void* obj, va_list args), ...);

	void NodeForEach(NODE** list, void (*pAction)(NODE* node), NODE** iterator);

	void NodeProcessRepeat(NODE* process_to_repeat,
		NODE** iterator);



#ifdef __cplusplus
}
#endif

#endif // !NODE_H

