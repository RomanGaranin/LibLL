/*
	Roman Garanin
*/
#include "../Inc/Node.h"


NODE* Stub = 0;

void Node_Init_Stub(NODE* stub)
{
	Stub = stub;
}

void Node_Connect(NODE** List, NODE* node, NODE** iterator)
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
	if (*List == Stub)
	{

		*List = node;
		*iterator = *List;
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


void Node_Insert(NODE* node, NODE* insert_node, NODE** iterator)
{
	if ((!node))
	{
		return;
	}
	if (!iterator)
	{
		return;
	}
	if (!*iterator)
	{
		return;
	}
	if (!insert_node)
	{
		return;
	}
	if (node->next == *iterator)
	{
		*iterator = insert_node;
	}
	insert_node->next = node->next;
	insert_node->prev = node;
	node->next->prev = insert_node;
	node->next = insert_node;
}


void Node_Disconnect(NODE** List, NODE* node, NODE** iterator)
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
			if (node == *iterator)
			{
				*iterator = node->next;
			}
			if (nd == *List)							 // The node is the first in the list.
			{
				if (nd->next == *List)					 // Only one node in the list.
				{
					*iterator = Stub;
					*List = Stub;
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



void Node_Disconnect_First(NODE** List, NODE** deleted_node, NODE** iterator)
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


void Node_Change_List(NODE** SrcList, NODE** DestList, NODE* node, NODE** s_iterator, NODE** d_iterator)
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
	Node_Disconnect(SrcList, node, s_iterator);
	Node_Connect(DestList, node, d_iterator);
	return;
}


void Node_Change_List_Insert(NODE** SrcList,
	NODE* insert_after,
	NODE* node,
	NODE** s_iterator,
	NODE** d_iterator)
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
	Node_Disconnect(SrcList, node, s_iterator);
	Node_Insert(insert_after, node, d_iterator);
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
	printf("List deleted:\r\n");
	while (*List != Stub)
	{

		Node_Disconnect_First(List, &del_node, 0);
		printf("%d  == %p == - %d\r\n", cnt, del_node, del_node->ID);
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

void NodeForEach(NODE** list, void (*pAction)(NODE* node), NODE** iterator)
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
		*iterator = node->next;
		pAction(node);
		node = *iterator;
	} while ((*iterator != *list) && (*list != Stub));
	return;
}

void IterateBack(NODE** iterator)
{
	*iterator = (*iterator)->prev;
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
		printf("== %p == ID - %d\r\n", (void*)node, node->ID);
		node = next;
		cnt++;
	} while (next != list_to_print);

	printf("\r\n\r\n");
	return;
}


