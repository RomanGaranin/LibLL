#include "..\Inc\ForExampleModule.h"
/*
	Roman Garanin
	23.09.2019
*/


void ModuleProcessStub(struct _process* mdl_prc);

void ModuleProcessStub(struct _process* mdl_prc)
{
	printf("Module process ID %d ...\r\n", (mdl_prc)->ProcessID);
	/*
		Module process...
	*/
	Node_Change_List((NODE * *)& ProcessList, (NODE**)&ModuleList, (NODE*)mdl_prc);
}

void ModuleAdd(MODULE* module)
{
	module->process.Process = ModuleProcessStub;
	Node_Connect((NODE * *)& ProcessList, (NODE*)module);
}
