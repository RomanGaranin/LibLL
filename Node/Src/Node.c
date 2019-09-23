/*
	Roman Garanin
*/
#include "../Inc/Node.h"


NODE* Stub;

void Node_Init_Stub(NODE* stub)
{
	Stub = stub;
}



void Node_Connect(NODE** List, NODE* node)
{
	if ((!node)&&(!List))
	{
		return;
	}
	if (*List == Stub)
	{
		*List = node;
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

void Node_Disconnect(NODE** List, NODE* node)
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
			if (nd == *List)							 // The node is the first in the list.
			{
				if (nd->next == *List)					 // Only one node in the list.
				{
					*List = Stub;
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
	} while (nd!=*List);
}

void Node_Disconnect_First(NODE** List, NODE** deleted_node)
{
	if (!List)
	{
		return;
	}
	if (!*List)
	{
		return;
	}
	if ((*List)->next == *List)		// We have only one node
	{
		*deleted_node = *List;
		*List = Stub;
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

void Node_Change_List(NODE** SrcList, NODE** DestList, NODE* node)
{
	if ((!SrcList) && (!DestList))
	{
		return;
	}
	if ((!*SrcList) && (*DestList))
	{
		return;
	}
	if (!node)
	{
		return;
	}

		Node_Disconnect(SrcList, node);
		Node_Connect(DestList, node);

	if (*SrcList == Stub)
	{
		node = Stub;
	}
	return;
}

void Node_Clear_List(NODE** List)
{
	if ((!List)&&(!*List))
	{
		return;
	}
	NODE* delete_node = 0;
	while (*List!= Stub)
	{
		Node_Disconnect_First(List, &delete_node);
		free(delete_node);
	}
	*List = Stub;
	return;
}
void NodeCheckList(NODE* List, NODE** node)
{
	if (List == Stub)
	{
		*node = Stub;
	}
}
NODE* NodeGoNext(NODE* List, NODE* node)
{
	if (!node)
	{
		return;
	}
	NODE* nd = node;
	nd = node->next;
	return nd;
}

NODE* NodeFind(NODE* List, bool (*pCheckSign)(void* obj, va_list args), ...)
{
	if (!List)
	{
		return;
	}
	if (!pCheckSign)
	{
		return;
	}

	NODE* node = List;
	va_list args;
	va_start(args, pCheckSign);

	if (!pCheckSign)
	{
		return NULL;
	}
	do
	{
		if (pCheckSign((void*)node, args))
		{
			return node;
		}
		node = node->next;
	} while (node!=List);

	va_end(args);

	return NULL;
}


