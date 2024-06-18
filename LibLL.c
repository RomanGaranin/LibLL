/**
* \file    LibLL.c
* \brief   Linked list library implementation.
*	
* Abbreviations:
* LL - Linked list.
*	
* \author    Roman Garanin
* \copyright Roman Garanin
*/

#include "LibLL.h"

#ifdef DEBUG
#define DEBUG_PRINT(...); printf(__VA_ARGS__);
#else
#define DEBUG_PRINT(...);
#endif

static void StubAction(NODE *node);
static void StubEmptyAction(NODE *node);
struct stub_node
{
	NODE node;
	void (*pStubAction)(NODE* node);
};

const struct stub_node Stub =
{
	.node =
	{
		.next = (NODE*)&Stub,
		.prev = (NODE*)&Stub,
	},
	.pStubAction = StubAction
};

static void StubAction(NODE* node)
{
	DEBUG_PRINT("List is empty ...\n");
	Stub.pStubAction = StubEmptyAction;
}

static void StubAmptyAction(NODE* node)
{
	;
}
void LL_Connect(NODE** List, NODE* node, NODE** tmp)
{
	if (NULL == node) {
		return;
	}
	if (NULL == List) {
		return;
	} else {
		if ((NULL == *List)) {
			return;
		}
	}
	if (*List == (NODE*)&Stub) {
		*List = node;
		*tmp = *List;
		node->next = node;
		node->prev = node;
		return;
	}

    NODE *nd = (*List)->prev;

	nd->next = node;
	node->prev = nd;
	node->next = *List;
	(*List)->prev = node;
	return;
}

void LL_Insert(NODE* node, NODE* insert_node, NODE** tmp)
{
	if ((NULL == node)) {
		return;
	}
	if (NULL == tmp) {
		return;
	}
	if (NULL == *tmp) {
		return;
	}
	if (NULL == insert_node) {
		return;
	}
	if (node->next == *tmp) {
		*tmp = insert_node;
	}
	insert_node->next = node->next;
	insert_node->prev = node;
	node->next->prev = insert_node;
	node->next = insert_node;
}

void LL_Disconnect(NODE** List, NODE* node, NODE** tmp)
{
	if ((NULL == node)) {
		return;
	}
	if (NULL == List) {
		return;
	}
	if (NULL == *List) {
		return;
	}

	if (node == *tmp) {
				*tmp = node->next;
	}

	if (node == *List) {					     // The node is the first in the list.
		if (node->next == *List) {				 // Only one node in the list.
		    *tmp = (NODE*)&Stub;
		    *List = (NODE*)&Stub;
		    Stub.pStubAction = StubAction;
		    return;
		} else {  
			(*List)->next->prev = (*List)->prev; // Connect next node (second in the list) to the last 
			(*List)->prev->next = (*List)->next; // Connect last node in the list to the second node in the list
			*List = (*List)->next;				 // The second node in the list becomes first			
		}
		node->next = node;
		node->prev = node;
		return;
	}
	node->prev->next = node->next;
	node->next->prev = node->prev;
	node->next = node;
	node->prev = node;
	return;
}

void LL_Disconnect_First(NODE** List, NODE** deleted_node, NODE** tmp)
{
	if (NULL == List) {
		*deleted_node = NULL;
		return;
	}
	if (NULL == *List) {
		*deleted_node = NULL;
		return;
	}
	if ( *List == (NODE*)&Stub ) {
		*deleted_node = NULL;
		return;

	}
	if ((*List)->next == *List)	{				// We have only one node
		*deleted_node = *List;
		*List = (NODE*)&Stub;
		Stub.pStubAction = StubAction;
		return;
	} else {
		*deleted_node = *List;
		(*List)->next->prev = (*List)->prev;	// Connect next node (second in the list) to the last 
		(*List)->prev->next = (*List)->next;	// Connect last node in the list to the second node in the list
		*List = (*List)->next;					// The second node in the list becomes first  
		(*deleted_node)->next = *deleted_node;
		(*deleted_node)->prev = *deleted_node;
		return;
	}
}

void LL_Change_List(NODE** SrcList, NODE** DestList, NODE* node, NODE** s_tmp, NODE** d_tmp)
{
	if (NULL == SrcList) {
		return;
	}
	else {
		if (NULL == *SrcList) {
			return;
		}
	}
	if (NULL == DestList) {
		return;
	}
	else {
		if (NULL == *DestList) {
			return;
		}
	}
	if (NULL == node) {
		return;
	}
	LL_Disconnect(SrcList, node, s_tmp);
	LL_Connect(DestList, node, d_tmp);
	return;
}

void LL_Change_List_Insert(NODE** SrcList, NODE* insert_after, NODE* node, NODE** s_tmp, NODE** d_tmp)
{
	if (NULL == SrcList) {
		return;
	} else {
		if (NULL == *SrcList) {
			return;
		}
	}
	if (NULL == insert_after) {
		return;
	}
	if (NULL == node) {
		return;
	}
	LL_Disconnect(SrcList, node, s_tmp);
	LL_Insert(insert_after, node, d_tmp);
	return;
}

void LL_Clear_List(NODE** List)
{
	if (NULL == List) {
		return;
	} else {
		if (NULL == *List) {
			return;
		}
	}
	static NODE* del_node = 0;
	uint16_t cnt = 1;
	DEBUG_PRINT("List deleted:\r\n");
	while (*List != (NODE*)&Stub)
	{
		LL_Disconnect_First(List, &del_node, 0);
		free(del_node);
		cnt++;
	}
	return;
}

NODE* LL_Find(NODE* start_node, enum dir direction, bool (*pCheckSign)(void* obj, va_list args), ...)
{
	if (NULL == start_node) {
		return NULL;
	} if (NULL == pCheckSign) {
		return NULL;
	}
	NODE* node = start_node;
	va_list args;
	va_start(args, pCheckSign);

	if (NULL == pCheckSign) {
		return NULL;
	}

	do {
		if (direction == Next) {
			node = node->next;
		}
		else if (direction == Prev) {
			node = node->prev;
		}
		if (pCheckSign((void*)node, args)) {
			return node;
		}
	} while (node != start_node);
	va_end(args);
	return NULL;
}

void LL_ForEach(NODE** list, NODE* (*pAction)(NODE* node), NODE** tmp)
{
	if (NULL == list) {
		return;
	} if (NULL == pAction) {
		return;
	}

	if (*list == (NODE*)&Stub) {
          Stub.pStubAction((NODE*)&Stub);
          return;
	}

	NODE* node = *list;
	do {
		*tmp = node->next;
		pAction(node);
		node = *tmp;
        } while ((*tmp != *list) && (*list != (NODE *)&Stub));
	return;
}
