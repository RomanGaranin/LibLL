/*
	Roman Garanin
	18.09.2019
*/
#include "../Inc/Process.h"

void ProcessStubFunc(void* obj);

PROCESS ProcessStub =
{
	{
		.next = (NODE*)& ProcessStub,
		.prev = (NODE*)& ProcessStub,
	},
	.Process = ProcessStubFunc, 
};


void ProcessStubFunc(void* obj)
{ 
	static bool lock = true;
	if (lock)
	{
		printf("No processes...\r\n");
		lock = false;
	}
	return;
}

PROCESS* ProcessList = &ProcessStub;
PROCESS* process = &ProcessStub;

void Processes()
{
	process->Process(process);
	//process = (PROCESS*)process->node.next;
}

 

