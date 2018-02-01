/*
	负责整个队列系统的模拟
*/
#ifndef QueueSystem_hpp
#define QueueSystem_hpp

#include "Event.hpp"
#include "Queue.hpp"
#include "ServiceWindow.hpp"

class QueueSystem {

public:

	QueueSystem(int total_service_time, int window_num);   //初始化队列系统


	~QueueSystem();   //销毁


	void simulate(int simulate_num);   //启动模拟

	inline double getAvgStayTime() {
		return avg_stay_time;   //平均逗留时间
	}
	inline double getAvgCustomers() {
		return avg_customers;   //每分钟平均顾客数
	}

private:
	
	double run();   //队列系统运行一次

	
	void init();   //初始化各种参数


	void end();  //清空各种参数

	
	int getIdleServiceWindow();   //获得空闲窗口索引

	
	void customerArrived();   //处理顾客到达事件

	
	void customerDeparture();  //处理顾客离开事件

	
	int window_num;   //服务窗口的总数

	 
	int total_service_time;   //总的服务时间

	
	int total_customer_stay_time;   //总的逗留时间

	
	int total_customer_num;  //总顾客数

	//62-65 核心成员
	ServiceWindow*  windows;
	Queue<Customer> customer_list;
	Queue<Event>       event_list;
	Event*          current_event;

	//给外部调用的结果
	double avg_customers;
	double avg_stay_time;

};


#endif 