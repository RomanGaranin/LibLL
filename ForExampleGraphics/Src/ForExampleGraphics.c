/*
	Roman Garanin
	17.09.2019
*/

#include "../Inc/ForExampleGraphis.h"
#include "string.h"

GO_HEADER* GrapicsList = (GO_HEADER*)& ProcessStub;

static void DrawStub(struct _process* go_prc);

static void DrawStub(struct _process* go_prc)
{
	GO_HEADER* hdr = (GO_HEADER*)
	printf("Draw %d \r\n", (go_prc)->ProcessID);
	/*
		Draw...
	*/
	static bool lock = true;

	if (lock)
	{
		NodeProcessRepeat(go_prc);
		lock = false;
	}
	else
	{
	 NodeStopProcess((NODE * *)&ProcessList, (NODE * *)&GrapicsList, (NODE*)go_prc);
		lock = true;
	}
}

static void GO_Stubf(void* go)
{
	return;
}


void GO_Add(GO_HEADER* go)
{
	go->Action = 0;
	go->process.Process = DrawStub;
	go->state = GO_SWITCHABLE | GO_DRAW;

	Process_Start((PROCESS **)& ProcessList, (PROCESS*)go);
}

bool GO_Check(void* obj, va_list args)
{
	GO_HEADER* go = (GO_HEADER*)obj;
	uint8_t fstr[100];
	uint8_t* fstr_ptr = va_arg(args, uint8_t*);
	uint16_t p;
	strcpy(fstr, fstr_ptr);
	uint8_t* str = (uint8_t*)strtok(fstr, " ");

	bool ID = true;
	bool group = true;
	bool state = true;

	p = va_arg(args, uint16_t);

	while (str)
	{
		if (!strcmp("id", str))
		{
			ID = false;
			if (p == go->ID)
			{
				ID = true;
			}
			p = va_arg(args, uint16_t);
		}
		else if (!strcmp("gr", str))
		{
			group = false;
			if (p == go->GroupID)
			{
				group = true;
			}
			p = va_arg(args, uint16_t);
		}
		else if (!strcmp("st", str))
		{
			state = false;
			if (p & go->state)
			{
				state = true;
			}
			p = va_arg(args, uint16_t);
		}
		else
		{
			return false;
		}
		str = (uint8_t*)strtok(NULL, " ");
	}
	va_end(args);
	return (ID && group && state);
}