#include "Fsm.h"
using namespace FsmSpace;
Fsm::Fsm()
{
	
}
Fsm::~Fsm()
{
	
}


void Fsm::FSM_Regist(FSM_t* pFsm,FsmTable_t* pTable)
{
	pFsm->FsmTable=pTable;
}

void Fsm::FSM_StateTransfer(FSM_t* pFsm,int state)
{
	pFsm->curState=state;
}

void Fsm::FSM_EventHandle(FSM_t* pFsm,int event)
{
	FsmTable_t* pActTable = pFsm->FsmTable;
	void (*eventActFun)() = NULL;
	int nextState;
	int curState= pFsm->curState;
	int flag =0 ;
	
	for( int i=0 ; i< g_max_num ; i++)
	{
		if(event == pActTable[i].event)
		{
			if( curState == pActTable[i].curState )
			{
				flag=1;
				eventActFun = pActTable[i].eventActFun;
				nextState = pActTable[i].nextState;
				break;
			}
		}
	}
	
	if (flag)
	{
		if(eventActFun)
		{
			eventActFun();
		}
		FSM_StateTransfer(pFsm,nextState);
	}
	
	else
	{
		
	}	
}


void Fsm::InitFsm(FSM_t* pFsm,FsmTable_t changeTable[],int num)
{
	g_max_num = num;
	pFsm->curState = Monday;
	FSM_Regist(pFsm,changeTable);
}

void Fsm::polling_day(int *event)
{
	
	if(*event == 7)
	{
		*event =1;
	}
	else
	{
		(*event)++;
	}
}


