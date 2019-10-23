/*
	Roman Garanin
	17.09.2019
*/

#include "../Inc/ForExampleGraphis.h"
#include "string.h"

GO_HEADER* GraphicsList = (GO_HEADER*)& ProcessStub;
GO_HEADER* GO_Iterator = (GO_HEADER*)&ProcessStub;

static void DrawStub(NODE* go_prc);

static void DrawStub(NODE* go_prc)
{
	GO_HEADER* hdr = (GO_HEADER*)go_prc;
	printf("Draw %d \r\n", hdr->process.ProcessID);
	/*
		Draw...
	*/
	static bool lock = true;

	if (lock)
	{
		uProcessRepeat(go_prc, &PLProcessIterator);
		lock = false;
	}
	else
	{
		uProcessStop(&GraphicsList, go_prc);
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

	uProcessStart(go);
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