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
PROCESS* ProcessNext	= &ProcessStub;
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
		Node_Connect((NODE **) process_list, (NODE*)process_to_start);
		Process = *process_list;
	}
	else
	{
		Node_Connect((NODE * *)process_list, (NODE*)process_to_start);
	}
	return;
}


void Process_Stop(PROCESS** process_list, PROCESS** process_stop_list, PROCESS* process_to_stop)
{
	if (!process_list)
	{
		return;
	}
	else
	{
		if (!*process_list)
		{
			return;
		}
	}
	if ((!*process_stop_list))
	{
		return;
	}
	else
	{
		if ((!*process_stop_list) && (!process_to_stop))
		{
			return;
		}
	}


	Node_Change_List((NODE**)process_list,(NODE**)process_stop_list,(NODE*)process_to_stop);

	if (*process_list == &ProcessStub)
	{
		ProcessNext = &ProcessStub;
	}
	return;
}

void Processes()
{

	ProcessNext = (PROCESS*)Process->node.next;
	Process->Process(Process);
	Process = ProcessNext;
}

 

