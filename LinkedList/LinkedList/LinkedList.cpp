/*
	Roman Garanin
*/
#include "stdlib.h"
#include "stdio.h"
#include "stdbool.h"
#include "stdarg.h"
#include "../../Node/Inc/Node.h"

#define GO_DRAW				(uint16_t)0x02
#define GO_FOCUS			(uint16_t)0x04
#define GO_PRESS			(uint16_t)0x08
#define GO_LONG_PRESS		(uint16_t)0x10
#define GO_LONG_BORDER		(uint16_t)0x20
#define GO_STATE			(uint16_t)0x40
#define GO_ONOFF			(uint16_t)0x80
#define GO_LIGHT			(uint16_t)0x100
#define GO_SWITCHABLE		(uint16_t)0x200
#define GO_HOLDABLE			(uint16_t)0x400
#define GO_LONG_PRESSABLE   (uint16_t)0x800
#define GO_LOCK				(uint16_t)0x1000	
#define GO_OFFHOLDABLE		(uint16_t)0x2000
#define GO_TOUCHABLE		(uint16_t)0x4000
#define GO_SELECTED			(uint16_t)0x8000

NODE* MainList = 0;
NODE* EraseList = 0;
NODE* ActionList = 0;

void DrawStub(void* go);
void GO_Stubf(void* go);


typedef struct go_states
{
	unsigned global_draw : 1;
	unsigned draw : 1;
	unsigned focus : 1;
	unsigned press : 1;
	unsigned longPress : 1;
	unsigned border : 1;
	unsigned state : 1;
	unsigned onoff : 1;
	unsigned Light : 1;
	unsigned switchable : 1;
	unsigned holdable : 1;
	unsigned longPressAvailable : 1;
	unsigned lock : 1;
	unsigned OffHoldable : 1;
	unsigned touchable : 1;
	unsigned selected : 1;
}GO_STATES;

typedef struct go_header
{
	NODE node;
	uint16_t ID;
	uint16_t GroupID;
	uint16_t state;
	void(*Draw)(void* go);
	void(*Action)();
}GO_HEADER;


bool CheckSign (void* obj, uint16_t sign);

bool GO_Check(void* obj, uint8_t* format_str, uint16_t sign, ...);

bool GO_Check(void* obj, uint8_t* format_str, uint16_t sign, ...)
{
	GO_HEADER* go = (GO_HEADER*)obj;
	uint8_t fstr[100]; 

	va_list args;
	uint16_t p;
	strcpy(fstr, format_str);
	uint8_t* str = strtok(fstr, " ");
	
	bool ID = true;
	bool group = true;
	bool state = true;

	va_start(args, sign);
	p = sign;
	

	while (str)
	{
		if (!strcmp("id",str))
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
			if (p == go->state)
			{
				state = true;
			}
			p = va_arg(args, uint16_t);
		}
		else
		{
			return;
		}
		str = strtok(NULL, " ");
		
	}
	va_end(args);

	return (ID && group && state);


}



bool CheckSign(void* obj, uint16_t sign)
{
	GO_HEADER* go = (GO_HEADER*)obj;

	if (sign == go->ID)
	{
		return true;
	}
	else
	{
		return false;
	}
}

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
	0, 
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
		if (!node)
		{
			return;
		}
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
		GO->GroupID = 0;
		GO->state = GO_DRAW;
		GO->ID = i;
		GO->node.ID = i;
		Node_Add((NODE**)&DrawList, (NODE*)GO);
	}


	GO = (GO_HEADER*)NodeFind(DrawList, CheckSign, 3);
	GO->state = (GO_ONOFF| GO_SWITCHABLE| GO_DRAW);
	GO->GroupID = 1;

	GO_Check((void*) GO, "id st", 3, (GO_SWITCHABLE | GO_DRAW));


	printf("%d\n", GO->ID);

	while (1)
	{
		DrawList->Draw((void*) DrawList);	
	}
}


