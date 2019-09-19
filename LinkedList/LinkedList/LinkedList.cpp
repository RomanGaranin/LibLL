/*
	Roman Garanin
*/
#define _CRT_SECURE_NO_WARNINGS

#include "stdlib.h"
#include "stdio.h"
#include "stdbool.h"
#include "stdarg.h"
#include "string.h"
#include "../../Node/Inc/Node.h"
#include "../../ForExampleGraphics/Inc/ForExampleGraphis.h"
#include "..//..//Process/Inc/Process.h"

int main()
{
	Node_Init_Stub(ProcessList);
	GrapicsList = ProcessList;
	for (uint8_t i = 0; i < 5; i++)
	{
		GO_HEADER* go = (GO_HEADER*)malloc(sizeof(GO_HEADER));
		go->ID = i;
		go->process.ProcessID = i;
		go->process.node.ID = i;
		GO_Add(go);
		
	}
	process = ProcessList;
	while (1)
	{
		Processes();
	}
}


