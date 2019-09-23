#ifndef  FOR_EXAMPLE_MODULE_H
#define  FOR_EXAMPLE_MODULE_H
#include "../../Node/Inc/Node.h"
#include "../../Process/Inc/Process.h"

typedef struct module
{
	PROCESS process;
	uint16_t NameID;
	uint16_t ClientNameID1;
	uint16_t ClientNameID2;
	uint16_t ProviderNameID1;
	uint16_t ProviderNameID2;
}MODULE;


MODULE* ModuleList;

void ModuleAdd(MODULE* module);

void ModuleProcessStub1(struct _process* mdl_prc);



#endif