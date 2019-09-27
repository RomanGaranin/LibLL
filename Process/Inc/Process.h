/*
	Roman Garanin
	18.09.2019
*/

#ifndef PROCESS_H
#define PROCESS_H
#include "../../Node/Inc/Node.h"


#ifdef __cplusplus
{
#endif

typedef struct _process
{
	NODE node;
	void(*Process)(struct _process* prc);
	uint32_t ProcessID;
}PROCESS;

extern PROCESS ProcessStub;
extern PROCESS* ProcessList;

void Process_Start(PROCESS** process_list, PROCESS* process_to_start);

void Process_Repeat(PROCESS* process_to_repeat);

void Process_Stop(PROCESS** process_list, PROCESS** process_stop_list, PROCESS* process_to_stop);

void Process_Restart(PROCESS** process_stop_list, PROCESS** process_list, PROCESS* process_to_restart);

void Processes();

#ifdef __cplusplus
}
#endif

#endif
