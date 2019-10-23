/*
	Roman Garanin
*/

#include "../Inc/Process.h"

static void ProcessStubFunc(NODE* prc);
PROCESS ProcessStub =
{
	{
		.next = (NODE*)&ProcessStub,
		.prev = (NODE*)&ProcessStub,
		.ID = 44444,
	},
	.Process = &ProcessStubFunc,
	.ProcessID = 44444
};

static void ProcessStubFunc(NODE* prc)
{
	printf("No processes...\r");
	return;
}
static void ProcessDeleteList(NODE* prc);

PROCESS ProcessDelete =
{
	{
		.next = (NODE*)&ProcessDelete,
		.prev = (NODE*)&ProcessDelete,
		.ID = 33333,
	},
	.Process = &ProcessDeleteList
};

bool process_del = false;

static void ProcessDeleteList(NODE* prc)
{
	Node_Clear_List((NODE**)&ProcessDelList);
	uProcessDisconnect(prc);
	process_del = false;
	return;
}

PROCESS* ProcessStopList = &ProcessStub;
PROCESS* SLProcessIterator = &ProcessStub;

PROCESS* ProcessList = &ProcessStub;
PROCESS* PLProcessIterator = &ProcessStub;

PROCESS* ProcessDelList = &ProcessStub;
PROCESS* DLProcessIterator = &ProcessStub;



void ProcessForEach(PROCESS** proccesslist)
{
	if (!proccesslist)
	{
		return;
	}
	PROCESS* process = *proccesslist;
	do
	{
		PLProcessIterator = (PROCESS*)process->node.next;
		process->Process((NODE*)process);
		process = (PROCESS*)PLProcessIterator;
	} while ((PLProcessIterator != *proccesslist));

	return;
}






