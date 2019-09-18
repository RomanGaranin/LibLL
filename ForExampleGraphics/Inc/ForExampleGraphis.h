/*
	Roman Garanin
	17.09.2019
*/
#ifndef GRAPHICS_TEST_H
#define GRAPHICS_TEST_H
#include "../../Node/Inc/Node.h"
#include "../../Process/Inc/Process.h"

/******************************************
*	Graphics objects states
*/
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

typedef struct go_header
{
	PROCESS process;
	uint16_t ID;
	uint16_t GroupID;
	uint16_t state;
	uint16_t type;
	uint16_t x;
	uint16_t y;
	uint16_t x_size;
	uint16_t y_Size;
	void(*Action)();
}GO_HEADER;

GO_HEADER GO_Stub;
GO_HEADER* GrapicsList;

bool GO_Check(void* obj, va_list args);

#endif