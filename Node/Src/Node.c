/*
	Roman Garanin
*/
#include "../Inc/Node.h"


static NODE* Stub = 0;
static NODE* next_node = 0;
void Node_Init_Stub(NODE* stub)
{
	Stub = stub;
}

void Node_Connect_to_Stub(NODE** node, NODE* stub)
{
	*node = stub;
}

void Node_Connect(NODE** List, NODE* node)
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
	if(!DestList)
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
		Node_Disconnect(SrcList, node);
		Node_Connect(DestList, node);	
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
	NODE* delete_node = 0;
	while (*List!= Stub)
	{
		Node_Disconnect_First(List, &delete_node);
		free(delete_node);
	}
	*List = Stub;
	return;
}

NODE* NodeFind(NODE* start_node, enum dir direction, bool (*pCheckSign)(void* obj, va_list args), ...)
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
		if (pCheckSign((void*)node, args))
		{
			return node;
		}
	} while (node = NodeGoTo(start_node, node, direction));

	va_end(args);

	return NULL;
}

NODE* NodeGoTo(NODE* start_node, NODE* node, enum dir direction)
{
	if (node == start_node)
	{
		return NULL;
	}
	if (direction == Next)
	{
		node = node->next;
		return node;
	}
	else if (direction == Prev)
	{
		node = node->prev;
		return node;
	}
	else
	{
		return NULL;
	}
}

NODE* NodeNext(NODE* start_node, NODE* node)
{
	if (node == start_node)
	{
		return NULL;
	}
	node = node->next;
	return node;
}

NODE* NodePrev(NODE* start_node, NODE* node)
{
	if (node == start_node)
	{
		return NULL;
	}
	node = node->prev;
	return node;
}


void NodeStopProcess(NODE** process_list, NODE** process_stop_list, NODE* process_to_stop)
{
	Node_Change_List((NODE **)process_list, (NODE **)process_stop_list, (NODE*)process_to_stop);
	if (*process_list == Stub)
	{
		next_node = Stub;
	}
}
void NodeRestartProcess(NODE** process_stop_list, NODE** process_list, NODE* process_to_restart)
{
	if (*process_list == Stub)
	{
		Node_Change_List((NODE**)process_stop_list, (NODE**)process_list, (NODE*)process_to_restart);
		next_node = *process_list;
	}
	else
	{
		Node_Change_List((NODE**)process_stop_list, (NODE**)process_list, (NODE*)process_to_restart);
	}
}


void NodeProcessRepeat(NODE* process_to_repeat)
{
	if (!process_to_repeat)
	{
		return;
	}
	next_node = process_to_repeat;
}

void NodeDo(NODE** node, void (pProcess)(NODE* nd))
{
	if (!node)
	{
		return;
	}
	next_node = (*node)->next;

	if (pProcess)
	{
		pProcess(*node);
	}
	*node = next_node;
	return;
}