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

#ifdef __cplusplus
extern "C" {
#endif

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

	void Node_Init_Stub(NODE* stub);
	void Node_Connect_to_Stub(NODE** node, NODE* stub);


	void Node_Connect(NODE** List, NODE* node);
	void Node_Disconnect(NODE** List, NODE* node);
	void Node_Disconnect_First(NODE** List, NODE** deleted_node);
	void Node_Change_List(NODE** SrcList, NODE** DestList, NODE* node);
	void Node_Clear_List(NODE** List);

	NODE* NodeFind(NODE* start_node, enum dir direction, bool (*pCheckSign)(void* obj, va_list args), ...);
	NODE* NodeGoTo(NODE* start_node, NODE* node, enum dir direction);
	NODE* NodeNext(NODE* start_node, NODE* node);
	NODE* NodePrev(NODE* start_node, NODE* node);

	void NodeStopProcess(NODE** process_list, NODE** process_stop_list, NODE* process_to_stop);
	void NodeRestartProcess(NODE** process_stop_list, NODE** process_list, NODE* process_to_restart);

	void NodeDo(NODE** node, void (pProcess)(NODE* nd));

#ifdef __cplusplus
}
#endif

#endif // !NODE_H

