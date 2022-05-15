/**
*	\file         LibLL.h
*	\brief        Linked list library implementation.
*	
*	Abbreviations:
*		LL - Linked list.
*	
*	\author       Roman Garanin
*	
*/

#ifndef LIBLL_H
#define LIBLL_H
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

/**     
*	\brief Global Stub for all linked lists.
*		   This stub contain the NODE struct and a pointer to stub function.
*/
extern const struct stub_node Stub;

/**
*	\brief Macro for declaration and initialisation a new linked list pointer.
*	\param ListName - The name for new linked list.
*/
#define mCREATE_LIST(ListName, ListTmp)\
	NODE* ListName = (NODE*)&Stub;\
	NODE* ListTmp = (NODE*)&Stub;


#define mINIT_NODE(node)\
	(NODE *)node->next = (NODE*)node;\
	(NODE *)node->prev = (NODE*)node;

/**
*	\struct
*	\brief Base node struct.
*/
typedef struct _node
{
	struct _node* next;  /**< The pointer to the next node */
	struct _node* prev;  /**< The pointer to the previous node */
}NODE;


/**
*	\brief Function connects the node to the end of the linked list.
*	\param List - The pointer to pointer to the linked list.
*	\param node - The pointer to node to be disconnected.
*	\return - no.
*/
void LL_Connect(NODE** List, NODE* node, NODE** tmp);

/**
*	\brief Function inserts the node to the linked list.
*	\param node - The node after which the new node will be inserted.
*  	\param insert_node - The node to insert.
*	\param tmp - Global pointer to pointer uses for iterate the linked list.
*					  Each linked list should have its own tmp.
*	\return - no.
*/
void LL_Insert(NODE* node, NODE* insert_node, NODE** tmp);

/**
*	\brief Function disconnects the node from linked list.
*	\param List - The pointer to pointer to the linked list.
*	\param node - The node to disconnect.
*	\param tmp - Global pointer to pointer uses for iterate the linked list.
*					  Each linked list should have its own tmp.
*	\return - no.
*/
void LL_Disconnect(NODE** List, NODE* node, NODE** tmp);

/**
*	\brief Function disconnects the first node from linked list.
*	\param List - The pointer to pointer to the linked list.
*	\param deleted_node - External pointer to pointer. The first disconnected node will be assigned to that pointer.
*	\param tmp - Global pointer to pointer uses for iterate the linked list.
*					  Each linked list should have its own tmp.
*	\return - no.
*/
void LL_Disconnect_First(NODE** List, NODE** deleted_node, NODE** tmp);

/**
*	\brief Function disconnects the node from the source linked list and then connects it to the end of destination linked list.
*	\param SrcList - The Pointer to pointer to the source linked list.
*	\param DstList - The Pointer to pointer to the destination linked list.
*	\param sl_tmp - Global pointer to pointer uses for iterate the  source linked list.
*	\param dl_tmp - Global pointer to pointer uses for iterate the destination linked list.
*			Each linked list should have its own tmp.
*	\param node - The pointer.
*	\return - no.
*/
void LL_Change_List(NODE** SrcList, NODE** DestList, NODE* node, NODE** sl_tmp, NODE** dl_tmp);


/**
*	\brief Function disconnects the node from the source linked list and then inserts it to the destination linked list.
*	\param SrcList - The Pointer to pointer to the source linked list.
*	\param insert_after - The Pointer to node in the destination list after which the node will insert.
*	\param node - Global pointer to pointer uses for iterate the  source linked list.
*	\param sl_tmp - Global pointer to pointer uses for iterate the  source linked list.
*	\param dl_tmp - Global pointer to pointer uses for iterate the destination linked list.
*			Each linked list should have its own tmp.
*	\param node - The pointer.
*	\return - no.
*/
void LL_Change_List_Insert(NODE** SrcList, NODE* insert_after, NODE* node,NODE** sl_tmp, NODE** dl_tmp);

/*!
*	\brief Function disconnects all nodes from the linked list and than free the memory.
*	\param List - Pointer to pointer to the linked list.
*	\return - no.
*/
void LL_Clear_List(NODE** List);

/**
 *	\brief Enum defines a direction for searching the nodes in the linked lists.
 */
enum dir { Next = 0, Prev };

/**
*	\brief Function finds the node in the linked list by the check signs function.
*	\param start_node - The pointer to the node from which starts the search.
*	\param direction - The direction for searching.
*	\param CheckSign - The pointer to the check signs function.
*	\param ... - The sequence of parameters that passes to the check signs function.
*	\return Pointer to the finded node.
*/
NODE* LL_Find(NODE* start_node, enum dir direction, bool (*pCheckSign)(void* obj, va_list args), ...);

/**
*	\brief Function iterates the linked list and call the action (pointer to function) passed as a parameter to that function.
*	\param pAction - Pointer to function that will call for each node in the linked list.
					 This function should receive a pointer to the current node as a parameter.
*	\param tmp -     Global pointer to pointer uses for iterate the linked list.
*					 Each linked list should have its own tempore node .
*	\return - no.
*/
void LL_ForEach(NODE** list, NODE* (*pAction)(NODE* node), NODE** tmp);

#define LIST_FOREACH(l, list)\
		for(l = (list)->next; l != (list); l = l->next)

#define	list_for_each_safe(p, n, head)					\
	for (p = (head)->next, n = p->next; p != (head); p = n, n = p->next)

#ifdef __cplusplus
}
#endif

#endif // !LIBLL_H
