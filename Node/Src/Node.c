/*
	Roman Garanin
*/
#include "../Inc/Node.h"

typedef struct node
{
	struct node* next;
	struct node* prev;
}NODE;

static NODE NodeStub =
{
	&NodeStub,
	&NodeStub
};

void Node_Add(NODE** List, NODE* node)
{
	if ((!node)||(!List))
	{
		return;
	}
}

void Node_Del(NODE** List, NODE* node)
{
	if ((!node) || (!List))
	{
		return;
	}
}

void Node_Del_First(NODE** List, NODE* node)
{
	if ((!node) || (!List))
	{
		return;
	}
}
