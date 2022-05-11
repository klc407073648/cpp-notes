#ifndef _FSM_H_
#define _FSM_H_

#include <iostream>
#include <string>

using namespace std;

/**
* @brief 状态表结构
* @param[in] event 		 事件
* @param[in] curState 	 当前状态
* @param[in] eventActFun 函数指针名
* @param[in] nextState 	 下一个状态
*/
struct  FsmTable_t
{
	int event;
	int curState;
	void (*eventActFun)();
	int nextState;	
};

/**
* @brief 状态机对象
* @param[in] FsmTable 	 指向的状态表
* @param[in] curState 	 当前状态
*/
struct FSM_t 
{
	FsmTable_t* FsmTable;
	int curState;		
};


namespace FsmSpace
{
	/**
	 * @brief 日期
	 */
	enum Week{
		Monday =1,
		Tuesday,
		Wednesday,
		Thursday,
		Friday,
		Saturday,
		Sunday ,
	};
	
	/**
	 * @brief 事件
	 */
	enum Event{
		EVENT1 = 1,
		EVENT2 ,
		EVENT3 ,
		EVENT4 ,
		EVENT5 ,
		EVENT6 ,
		EVENT7 ,
	};
	
	/**
	 * @brief 状态机类
	 */
	class Fsm
	{	
		public:
			//typedef std::function<void()> eventDeal; 
			/**
			 * @brief 构造函数
			 */
			Fsm();
			
			/**
			 * @brief 析构函数
			 */
			~Fsm();
			
			/**
			 * @brief 状态机注册
			 * @param[in] pFsm 	  状态机指针
			 * @param[in] pTable  状态表
			 */
			void FSM_Regist(FSM_t* pFsm,FsmTable_t* pTable);
			
			/**
			 * @brief 状态转换函数
			 * @param[in] pFsm 	 状态机指针
			 * @param[in] state  要转换的状态
			 */
			void FSM_StateTransfer(FSM_t* pFsm,int state);
			
			/**
			 * @brief 事件处理
			 * @param[in] pFsm 	 状态机指针
			 * @param[in] event  事件
			 */
			void FSM_EventHandle(FSM_t* pFsm,int event);
			
			/**
			 * @brief 初始化函数
			 * @param[in] pFsm 	 		状态机指针
			 * @param[in] changeTable 	状态转换列表
			 * @param[in] changeTable 	状态转换表数量
			 */
			void InitFsm(FSM_t* pFsm,FsmTable_t changeTable[],int num);
			
			/**
			 * @brief 日期转换函数(满7转换)
			 * @param[in] event 	 	事件
			 */
			void polling_day(int *event);
			
		private:
		    ///转换表数量
			int g_max_num;
	};
}

#endif //_FSM_H_