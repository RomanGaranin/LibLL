/*
	Roman Garanin
*/
#define _CRT_SECURE_NO_WARNINGS

#include "stdlib.h"
#include "stdio.h"
#include "stdbool.h"
#include "stdarg.h"
#include "string.h"
//#include "../../Node/Inc/Node.h"
#include "..//..//Process/Inc/Process.h"
#include "../../ForExampleGraphics/Inc/ForExampleGraphis.h"
#include "..//..//ForExampleModule/Inc/ForExampleModule.h"

#include "windows.h"


uint8_t* GetTime();

uint32_t GetSysTick();


int main()
{
/*
Connecting platform dependent functions to platform independent functions.

		 +-------------------------+------------------------+
		 |    Windows depenednt    |       Independet       |
		 +--------------------------------------------------+
		 |                         |                        |
		 |       GetTime     <-----------+ pGetTime         |
		 |                         |                        |
				 GetSysTick  <-----------+ pGetSysTick
		 |                         |                        |
		 +-------------------------+------------------------+            */

	InitGetTime(GetTime);			
	InitGetSysTick(GetSysTick);


	Node_Init_Stub(ProcessList);						//Init Stub for nodes

	for (uint8_t i = 0; i < 5; i++)
	{
		MODULE* mdl = (MODULE*)malloc(sizeof(MODULE));
		if (!mdl)
		{
			return;
		}
		mdl->NameID = i;
		mdl->process.ProcessID = i;
		mdl->process.node.ID = i;
		ModuleAdd(mdl);
	}
	for (uint8_t i = 0; i < 5; i++)
	{
		GO_HEADER* go = (GO_HEADER*)malloc(sizeof(GO_HEADER));
		if (!go)
		{
			return;
		}
		go->ID = i;
		go->process.ProcessID = i;
		go->process.node.ID = i;
		GO_Add(go);
	}

	for (uint8_t i = 10; i < 15; i++)
	{
		MODULE* mdl = (MODULE*)malloc(sizeof(MODULE));
		if (!mdl)
		{
			return;
		}
		mdl->NameID = i;
		mdl->process.ProcessID = i;
		mdl->process.node.ID = i;
		ModuleAdd(mdl);
	}

MODULE* mdl = (MODULE*)malloc(sizeof(MODULE));
if (!mdl)
{
	return;
}
mdl->NameID = 50;
mdl->process.ProcessID = 50;
mdl->process.node.ID = 50;
mdl->process.Process = ModuleProcessStub1;
ModuleAdd(mdl);
mdl->process.Process = ModuleProcessStub1;

	while (1)
	{
		ProcessForEach(&ProcessList);
	}
}

uint8_t* GetTime()
{
	static uint8_t timestr[100];
	SYSTEMTIME t;
	LPSYSTEMTIME lpSystemTime = &t;
	GetSystemTime(lpSystemTime);
	sprintf(timestr, "%d:%d:%d", lpSystemTime->wHour, lpSystemTime->wMinute, lpSystemTime->wSecond);
	return timestr;
}


uint32_t GetSysTick()
{
	uint32_t tick = (uint32_t)GetTickCount();
	return tick;
}
