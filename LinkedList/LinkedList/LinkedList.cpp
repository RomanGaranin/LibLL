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


#include "windows.h"


uint8_t* GetTime();

uint32_t GetSysTick();

int main()
{

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
