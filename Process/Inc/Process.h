/*
	Roman Garanin
	r_o.m.a_n@mail.ru
*/

#ifndef PROCESS_H
#define PROCESS_H
#include "../../Node/Inc/Node.h"

#ifdef __cplusplus
extern "C" {
#endif

	typedef struct _process
	{
		NODE node;
		void(*Process)(NODE* prc);
		uint32_t ProcessID;
	}PROCESS;
	/*!
	*		The stub process.
	*/
	extern PROCESS	ProcessStub;
	/*!
	*		Process contains a function for deleting processes from ProcessDelList.
	*/
	extern PROCESS  ProcessDelete;
	extern bool     process_del;


	extern PROCESS* ProcessStopList;
	extern PROCESS* SLProcessIterator;

	extern PROCESS* ProcessList;
	extern PROCESS* PLProcessIterator;

	extern PROCESS* ProcessDelList;
	extern PROCESS* DLProcessIterator;

	/*!
	*	\breif Function....
	*	\param proccesslist - process list.
	*	\return	None.
	*/
	void ProcessForEach(PROCESS** proccesslist);

	/*!
	*	\breif Macro....
	*	\param proccesslist - process list.
	*	\return	None.
	*/
#define uProcessRepeat(ptr,  it);  *(NODE**)it = (NODE*)ptr;

	/*!
	*	\breif Macro starts a new process (not from stop list).
	*	\param pts - process to start.
	*	\return	None.
	*/
#define uProcessStart(pts)				Node_Connect((NODE**)&ProcessList,\
													 (NODE*)pts,\
													 (NODE**)&PLProcessIterator);
	/*!
	*	\breif Macro stops a process (move process from process list to stop list).
	*	\param pts - process to stop.
	*	\param psl - processes stop list.
	*	\return	None.
	*/
#define uProcessStop(psl, pts)		   Node_Change_List((NODE**)&ProcessList,\
														(NODE**)psl,\
														(NODE*)pts,\
														(NODE**)&PLProcessIterator,\
														(NODE**)&SLProcessIterator)

	/*!
	*	\breif  Macro disconnects a process from process list (Just disconnect, not connect to any another lists)
	*	\param  pts - process to disconnect.
	*	\return	None.
	*/
#define uProcessDisconnect(ptd)			Node_Disconnect((NODE**)&ProcessList,\
														(NODE*)ptd,\
														(NODE**)&PLProcessIterator)

	/*!
	*	\breif Macro restarts a process (move a process from stop list to process list)
	*	\param ptr - process to restart.
	*	\param ptr - process stop list.
	*	\return	None.
	*/

#define uProcessRestart(psl, ptr)	      Node_Change_List((NODE**)psl,\
														   (NODE**)&ProcessList,\
														   (NODE*)ptr,\
														   (NODE**)&SLProcessIterator,\
														   (NODE**)&PLProcessIterator)	

	/*!
	*	\breif			Macro deletes processes from the delete list and frees memory.
	* 	\detailed		1. Moves process to delette list.
	*					2. Add Deleting process to the process list.
	*					3. When a deleting process will riched it delete all processes from the delete list
	*					   and then stop it self (move to stop list).
	*	\param			ptd - process to delete.
	*	\return			None.
	*/
#define uProcessDelete(ptd)			uProcessStop(&ProcessDelList, ptd);\
									if(!process_del)\
									{uProcessStart(&ProcessDelete); process_del = true;}

	/*!
	*	\breif  Macro iterates all process list.
	*	\param  None.
	*	\return	None.
	*/
#define uProcesses() next_node = Process->node.next;\
					 Process->Process((NODE*)Process);\
					 Process = (PROCESS*)next_node;			

#ifdef __cplusplus
}
#endif

#endif
