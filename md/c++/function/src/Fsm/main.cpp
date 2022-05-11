#include <iostream>
#include "Fsm.h"

using namespace FsmSpace;
void GetMonday()
{
	cout<<"I'm Monday"<<endl;
}

void GetTuesday()
{
	cout<<"I'm Tuesday"<<endl;
}

void GetWednesday()
{
	cout<<"I'm Wednesday"<<endl;
}

void GetThursday()
{
	cout<<"I'm Thursday"<<endl;
}

void GetFriday()
{
	cout<<"I'm Friday"<<endl;
}

void GetSaturday()
{
	cout<<"I'm Saturday"<<endl;
}

void GetSunday()
{
	cout<<"I'm Sunday"<<endl;
}
FsmTable_t changeTable[] =
{
	//1    		1 		函数 		2
	{EVENT1,Monday,GetMonday,Tuesday},
	{EVENT2,Tuesday,GetTuesday,Wednesday},
	{EVENT3,Wednesday,GetWednesday,Thursday},
	{EVENT4,Thursday,GetThursday,Friday},
	{EVENT5,Friday,GetFriday,Saturday},
	{EVENT6,Saturday,GetSaturday,Sunday},
	{EVENT7,Sunday,GetSunday,Monday},
};

int main()
{
	FSM_t fsm;
	Fsm* m_Fsm = new Fsm();
	int num= sizeof(changeTable) /sizeof(FsmTable_t);

	m_Fsm->InitFsm(&fsm,changeTable,num);
	int event = EVENT1;
	
	while(1)
	{
		cout<<"event "<<event<<" is coming ..."<<endl;
		m_Fsm->FSM_EventHandle(&fsm,event);
		cout<<"fsm current state "<<fsm.curState<<endl;
		m_Fsm->polling_day(&event);
		for(int i=0 ;i<10000;i++)
		{
			;
		}
	}
	return 0;
}