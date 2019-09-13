/*
	Roman Garanin
*/
#include "stdlib.h"
#include "../../Node/Inc/Node.h"


NODE* MainList = 0;
NODE* EraseList = 0;
NODE* ActionList = 0;


int main()
{
	//Create List (10 nodes)
	for (uint16_t i = 0; i < 10; i++)
	{
		NODE* node = (NODE*)malloc(sizeof(NODE));
		node->ID = i;
		Node_Add(&MainList, node);
	}

	//Change List (Move nodes from main list to erase list)
	while (MainList)
	{
		Node_Change_List(&MainList, &EraseList, MainList);
	}

	Node_Clear_List(&EraseList);

}


