/*
	Roman Garanin
	18.09.2019
*/

#ifndef PROCESS_H
#define PROCESS_H
#include "../../Node/Inc/Node.h"

typedef struct _process
{
	NODE node;
	void(*Process)(struct _process** obj);
	uint32_t ProcessID;
}PROCESS;

extern PROCESS* ProcessList;
extern PROCESS* process;

void Processes();


#endif
