/*
	Roman Garanin
*/
#include "stdlib.h"
#include "stdio.h"
#include "../../Node/Inc/Node.h"


NODE* MainList = 0;
NODE* EraseList = 0;
NODE* ActionList = 0;

void DrawStub(void* go);
void GO_Stubf(void* go);

typedef struct go_header
{
	NODE node;
	uint16_t ID;
	void(*Draw)(void* go);
	void(*Action)();
}GO_HEADER;


GO_HEADER* DrawList;
GO_HEADER* GrapicsList;


GO_HEADER GO_Stub =
{
	{
		0, 
		(NODE*)&GO_Stub,
		(NODE*)&GO_Stub
	},
	0, 
	GO_Stubf,
	0
};



void DrawStub(void* go)
{
	printf("Draw\r\n");
	Node_Change_List((NODE * *)& DrawList, (NODE * *)& GrapicsList, (NODE*)DrawList);
}

void GO_Stubf(void* go)
{
	return;
}


int main()
{
	NodeStub = (NODE*)& GO_Stub;
	//Create List (10 nodes)
	for (uint16_t i = 0; i < 10; i++)
	{
		NODE* node = (NODE*)malloc(sizeof(NODE));
		node->ID = i;
		Node_Add(&MainList, node);
	}

	//Change List (Move nodes from main list to erase list)
	while (MainList!=NodeStub)
	{
		Node_Change_List(&MainList, &EraseList, MainList);
	}
	Node_Clear_List(&EraseList);

	GO_HEADER* GO;
	for (uint16_t i = 0; i < 5; i++)
	{
		GO = (GO_HEADER*)malloc(sizeof(GO_HEADER));
		GO->Action = 0;
		GO->Draw = DrawStub;
		GO->ID = i;
		GO->node.ID = i;
		Node_Add((NODE**)&DrawList, (NODE*)GO);
	}

	while (1)
	{
		DrawList->Draw((void*) DrawList);	
	}
}


