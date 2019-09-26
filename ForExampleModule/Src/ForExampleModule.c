#include "..\Inc\ForExampleModule.h"
/*
	Roman Garanin
	23.09.2019
*/


MODULE* ModuleList = (MODULE*)&ProcessStub;

uint8_t* StubFunc();

uint32_t StubFunc1();

uint8_t* (*pGetTime)() = StubFunc;

uint32_t (*pGetSysTick)() = StubFunc1;


uint8_t* StubFunc()
{
	return "Stub...";
}

uint32_t StubFunc1()
{
	return 0;
}


void InitGetTime(uint8_t* (*ppGetTime)())
{
	pGetTime = ppGetTime;
}

void InitGetSysTick(uint32_t (*ppGetSysTick)())
{
	pGetSysTick = ppGetSysTick;
}

void ModuleProcessStub(struct _process* mdl_prc);

void ModuleProcessStub(struct _process* mdl_prc)
{
	printf("Module process ID %d ...\r\n", (mdl_prc)->ProcessID);
	/*
		Module process...
	*/
	Process_Stop((PROCESS**)& ProcessList, (PROCESS**)& ModuleList, (PROCESS*)mdl_prc);
}

void ModuleProcessStub1(struct _process* mdl_prc)
{
	printf("\rModule process ID %d  Time: %s", (mdl_prc)->ProcessID, pGetTime());
	static uint32_t time = 0;
	static bool lock = true;
	/*
		Module process...
	*/
	if (lock)
	{
		time = pGetSysTick();
		lock = false;
	}
	else
	{
		if (pGetSysTick() - time > 2000)
		{
			lock = true;
			printf("\nStop Module process ID %d  Time: %s \n", (mdl_prc)->ProcessID, pGetTime());
			Process_Stop((PROCESS * *)& ProcessList, (PROCESS * *)& ModuleList, (PROCESS*)mdl_prc);

			Process_Restart((PROCESS * *)& ModuleList, (PROCESS * *)& ProcessList, (PROCESS*)mdl_prc);
		}
	}
}

void ModuleAdd(MODULE* module)
{
	module->process.Process = ModuleProcessStub;
	Process_Start((PROCESS * *)& ProcessList, (PROCESS*)module);
}
