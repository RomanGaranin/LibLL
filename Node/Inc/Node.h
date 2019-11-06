/*
	Roman Garanin
	r_o.m.a_n@mail.ru
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

	/**************************************************************************************!
	*	\brief The base node struct. 
	*/
	typedef struct _node
	{
		struct _node* next;
		struct _node* prev;
		uint16_t ID;
	}NODE;

	/**************************************************************************************!
	*	\brief Enum defines a direction for searching the nodes in the linked lists.
	*/
	enum dir
	{
		Next = 0,
		Prev
	};
	extern  NODE* Stub;
	/**************************************************************************************!
	*	\brief Function for initialise the Stub node.
	*	\param stub - The pointer to the stub.
	*	\return - no.
	*/
	void Node_Init_Stub(NODE* stub);

	/**************************************************************************************!
	*	\brief Function connects the node to the end of the linked list.
	*	\param List - The pointer to pointer to the linked list.
	*	\param node - The pointer to node to be disconnected.
	*	\return - no.
	*/
	void Node_Connect(NODE** List, NODE* node, NODE** iterator);

	/**************************************************************************************!
	*	\brief Function inserts the node to the  linked list.
	*	\param List - The pointer to pointer to the linked list.
	*	\param node - The node after which the new node will be inserted.
	*	\param iterator - Global pointer to pointer uses for iterate the linked list.
	*					  Each linked list should have its own iterator.
	*	\return - no.
	*/
	void Node_Insert(NODE* node, NODE* insert_node, NODE** iterator);

	/**************************************************************************************!
	*	\brief Function disconnects the node from linked list.
	*	\param List - The pointer to pointer to the linked list.
	*	\param node - The node to disconnect.
	*	\param iterator - Global pointer to pointer uses for iterate the linked list.
	*					  Each linked list should have its own iterator.
	*	\return - no.
	*/
	void Node_Disconnect(NODE** List, NODE* node, NODE** iterator);

	/**************************************************************************************!
	*	\brief Function disconnects the first node from linked list.
	*	\param List - The pointer to pointer to the linked list.
	*	\param deleted_node - External pointer to pointer. The first disconnected node will be assigned to that pointer.
	*	\param iterator - Global pointer to pointer uses for iterate the linked list.
	*					  Each linked list should have its own iterator.
	*	\return - no.
	*/
	void Node_Disconnect_First(NODE** List, NODE** deleted_node, NODE** iterator);

	/**************************************************************************************!
	*	\brief Function disconnects the node from the source linked list and then connects it to the destination linked list.
	*	\param SrcList - The Pointer to pointer to the source linked list.
	*	\param DstList - The Pointer to pointer to the destination linked list.
	*	\sl_iterator - Global pointer to pointer uses for iterate the  source linked list.
	*	\dl_iterator - Global pointer to pointer uses for iterate the destination linked list.
	*				   Each linked list should have its own iterator.
	*	\param node - The pointer.
	*	\return no.
	*/
	void Node_Change_List(NODE** SrcList, NODE** DestList, NODE* node, NODE** sl_iterator, NODE** dl_iterator);

	/*!
	*	\brief Function disconnects all nodes from the linked list and than free the memory.
	*	\param List - Pointer to pointer to the linked list.
	*	\return no.
	*/
	void Node_Clear_List(NODE** List);

	/**************************************************************************************!
	*	\brief Function finds the node in the linked list by the check signs function.
	*	\param start_node - The pointer to the node from which starts the search.
	*	\param direction - The direction for searching.
	*	\param CheckSign - The pointer to the check signs function.
	*	\param ... - The sequence of parameters that passes to the check signs function.
	*	\return pointer to the finded node.
	*/
	NODE* NodeFind(NODE* start_node, enum dir direction, bool (*pCheckSign)(void* obj, va_list args), ...);

	/**************************************************************************************!
	*	\brief Function iterates the linked list and call the action (pointer to function) passed as a parameter to that function.
	*	\param pAction - Pointer to function that will call for each node in the linked list.
						 This function should receive a pointer to the current node as a parameter.
	*	\param iterator - Global pointer to pointer uses for iterate the linked list.
	*					  Each linked list should have its own iterator.
	*	\return no.
	*/
	void NodeForEach(NODE** list, void (*pAction)(NODE* node), NODE** iterator);

	/**************************************************************************************!
	*	\brief Function prints all list to standart output.
	*	\param list_to_print - Pointer to list for print.
	*	\return no.
	*/
	void PrintList(NODE* list_to_print);

#ifdef __cplusplus
}
#endif

#endif // !NODE_H

