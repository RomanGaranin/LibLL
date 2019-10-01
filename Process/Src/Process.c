/*
	Roman Garanin
	18.09.2019
*/

#include "../Inc/Process.h"
void ProcessStubFunc(struct _process* prc);

PROCESS ProcessStub =
{
	{
		.next = (NODE*)& ProcessStub,
		.prev = (NODE*)& ProcessStub,
	},
	.Process = &ProcessStubFunc, 
};

void ProcessStubFunc(struct _process* prc)
{ 
	printf("No processes...\r");
	return;
}

PROCESS* ProcessList	= &ProcessStub;
PROCESS* Process		= &ProcessStub;

void Process_Start(PROCESS** process_list, PROCESS* process_to_start)
{
	if ((!process_list))
	{
		return;
	}
	else
	{
		if ((!*process_list) && (!process_to_start))
		{
			return;
		}
	}
	if (*process_list == &ProcessStub)
	{
		Node_Connect((NODE **)process_list, (NODE*)process_to_start);
		Process = *process_list;
	}
	else
	{
		Node_Connect((NODE **)process_list, (NODE*)process_to_start);
	}
	return;
}

void Processes()
{
    NodeDo(&Process, Process->Process);
}

 

