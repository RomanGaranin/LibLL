/**
*	\file         Node.c
*	\brief        Linked list library implementation.
*	\author       Roman Garanin
*/

#include "../Inc/Node.h"

//#define PRINT_DEBUG
#ifdef PRINT_DEBUG

#define DEBUG_PRINT(...); printf(__VA_ARGS__);

#else

#define DEBUG_PRINT(...);

#endif

static void StubAction(NODE* node);
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
	DEBUG_PRINT("Stub...\n");
}

void Node_Connect(NODE** List, NODE* node, NODE** tmp)
{
	if (!node)
	{
		return;
	}

	if (!List)
	{
		return;
	}
	else
	{
		if ((!*List))
		{
			return;
		}
	}
	if (*List == (NODE*)&Stub)
	{

		*List = node;
		*tmp = *List;
		node->next = node;
		node->prev = node;


		return;
	}
	NODE* nd = *List;
	do
	{
		nd = nd->next;
	} while (nd->next != *List);
	nd->next = node;
	node->prev = nd;
	node->next = *List;
	(*List)->prev = node;
	return;
}


void Node_Insert(NODE* node, NODE* insert_node, NODE** tmp)
{
	if ((!node))
	{
		return;
	}
	if (!tmp)
	{
		return;
	}
	if (!*tmp)
	{
		return;
	}
	if (!insert_node)
	{
		return;
	}
	if (node->next == *tmp)
	{
		*tmp = insert_node;
	}
	insert_node->next = node->next;
	insert_node->prev = node;
	node->next->prev = insert_node;
	node->next = insert_node;
}


void Node_Disconnect(NODE** List, NODE* node, NODE** tmp)
{
	if ((!node))
	{
		return;
	}
	if (!List)
	{
		return;
	}
	if (!*List)
	{
		return;
	}
	NODE* nd = *List;
	do
	{
		if (node == nd)
		{
			if (node == *tmp)
			{
				*tmp = node->next;
			}
			if (nd == *List)							 // The node is the first in the list.
			{
				if (nd->next == *List)					 // Only one node in the list.
				{
					*tmp = (NODE*)&Stub;
					*List = (NODE*)&Stub;
					return;
				}
				else
				{
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
		nd = nd->next;
	} while (nd != *List);
}



void Node_Disconnect_First(NODE** List, NODE** deleted_node, NODE** tmp)
{
	if (!List)
	{
		return;
	}
	if (!*List)
	{
		return;
	}
	if ((*List)->next == *List)					// We have only one node
	{
		*deleted_node = *List;
		*List = (NODE*)&Stub;
		return;
	}
	else
	{
		*deleted_node = *List;
		(*List)->next->prev = (*List)->prev;	// Connect next node (second in the list) to the last 
		(*List)->prev->next = (*List)->next;	// Connect last node in the list to the second node in the list
		*List = (*List)->next;					// The second node in the list becomes first  
		(*deleted_node)->next = *deleted_node;
		(*deleted_node)->prev = *deleted_node;
		return;
	}
}


void Node_Change_List(NODE** SrcList, NODE** DestList, NODE* node, NODE** s_tmp, NODE** d_tmp)
{
	if (!SrcList)
	{
		return;
	}
	else
	{
		if (!*SrcList)
		{
			return;
		}
	}
	if (!DestList)
	{
		return;
	}
	else
	{
		if (!*DestList)
		{
			return;
		}
	}
	if (!node)
	{
		return;
	}
	Node_Disconnect(SrcList, node, s_tmp);
	Node_Connect(DestList, node, d_tmp);
	return;
}


void Node_Change_List_Insert(NODE** SrcList,
	NODE* insert_after,
	NODE* node,
	NODE** s_tmp,
	NODE** d_tmp)
{
	if (!SrcList)
	{
		return;
	}
	else
	{
		if (!*SrcList)
		{
			return;
		}
	}
	if (!insert_after)
	{
		return;
	}

	if (!node)
	{
		return;
	}
	Node_Disconnect(SrcList, node, s_tmp);
	Node_Insert(insert_after, node, d_tmp);
	return;
}


void Node_Clear_List(NODE** List)
{
	if (!List)
	{
		return;
	}
	else
	{
		if (!*List)
		{
			return;
		}
	}
	static NODE* del_node = 0;
	uint16_t cnt = 1;
	DEBUG_PRINT("List deleted:\r\n");
	while (*List != (NODE*)&Stub)
	{

		Node_Disconnect_First(List, &del_node, 0);
		free(del_node);
		cnt++;
	}
	return;
}

NODE* NodeFind(NODE* start_node,
	enum dir direction,
	bool (*pCheckSign)(void* obj, va_list args),
	...)
{
	if (!start_node)
	{
		return NULL;
	}
	if (!pCheckSign)
	{
		return NULL;
	}
	NODE* node = start_node;
	va_list args;
	va_start(args, pCheckSign);

	if (!pCheckSign)
	{
		return NULL;
	}

	do
	{
		if (direction == Next)
		{
			node = node->next;
		}
		else if (direction == Prev)
		{
			node = node->prev;
		}

		if (pCheckSign((void*)node, args))
		{
			return node;
		}

	} while (node != start_node);
	va_end(args);
	return NULL;
}

void NodeForEach(NODE** list, void (*pAction)(NODE* node), NODE** tmp)
{
	if (!list)
	{
		return;
	}
	if (!pAction)
	{
		return;
	}
	NODE* node = *list;
	do
	{
		*tmp = node->next;
		pAction(node);
		node = *tmp;
	} while ((*tmp != *list) && (*list != (NODE*)&Stub));
	return;
}

void IterateBack(NODE** tmp)
{
	*tmp = (*tmp)->prev;
	return;
}

void PrintList(NODE* list_to_print)
{
	NODE* node = list_to_print;
	NODE* next;
	uint16_t cnt = 0;
	do
	{
		next = node->next;
		node = next;
		cnt++;
	} while (next != list_to_print);

	DEBUG_PRINT("\r\n\r\n");
	return;
}


