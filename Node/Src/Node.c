/*
	Roman Garanin
*/
#include "../Inc/Node.h"

NODE* NodeStub = 0;

void Node_Add(NODE** List, NODE* node)
{
	if ((!node)&&(!List))
	{
		return;
	}
	if (!*List)
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

void Node_Del(NODE** List, NODE* node)
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
			if (nd == *List)// The node is the first in the list.
			{
				if (nd->next == *List)// Only one node in the list.
				{
					*List = NodeStub;
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

void Node_Del_First(NODE** List, NODE** deleted_node)
{
	if (!List)
	{
		return;
	}
	if (!*List)
	{
		return;
	}
	if ((*List)->next == *List)
	{
		*deleted_node = *List;
		*List = NodeStub;
		return;
	}
	else
	{
		*deleted_node = *List;
		(*List)->next->prev = (*List)->prev; // Connect next node (second in the list) to the last 
		(*List)->prev->next = (*List)->next; // Connect last node in the list to the second node in the list
		*List = (*List)->next;				 // The second node in the list becomes first  

		if ((*List)->next == *deleted_node)  //We have the last node in List
		{
			(*List)->next = *List;
		}
		//(*List)->prev = *List;
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
	Node_Del(SrcList, node);
	Node_Add(DestList, node);
}

void Node_Clear_List(NODE** List)
{
	NODE* delete_node = 0;
	while (*List!=NodeStub)
	{
		Node_Del_First(List, &delete_node);
		free(delete_node);
	}
	return;
}

NODE* NodeGoNext(NODE* List, NODE* node)
{
	NODE* nd = node;
	nd = node->next;
	return nd;
}

NODE* NodeFind(NODE* List, bool (*pCheckSign)(void* obj, uint8_t* fstring, va_list args), uint8_t* fstring, ...)
{
	NODE* node = List;

	va_list args;
	va_start(args, fstring);
	args = va_arg(args, uint16_t);

	if (!pCheckSign)
	{
		return NULL;
	}
	do
	{
		if (pCheckSign((void*)node, fstring, &args))
		{
			return node;
		}

		node = node->next;
	} while (node!=List);
	return NULL;
}


