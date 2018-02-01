#include "QueueSystem.hpp"
#include "Random.hpp"
#include "Event.hpp"

QueueSystem::QueueSystem(int total_service_time, int window_num) :
	total_service_time(total_service_time),
	window_num(window_num),
	total_customer_stay_time(0),
	total_customer_num(0) {
	this->windows = new ServiceWindow[window_num];   //创建服务窗口
}
QueueSystem::~QueueSystem() {
	delete[] windows;
}
void QueueSystem::simulate(int simulate_num) {
	double sum = 0;
	for (int i = 0; i != simulate_num; ++i) {
		sum += run();  // 每一遍运行，我们都要增加在这一次模拟中，顾客逗留了多久
	}
	avg_stay_time = (double)sum / simulate_num;    //计算平均逗留时间
	avg_customers = (double)total_customer_num / (total_service_time*simulate_num);  //计算每分钟平均顾客数
}

void QueueSystem::init() {      // 系统开启运行, 初始化事件链表, 部署第一个事件

	Event *event = new Event;  // 第一个事件肯定是到达事件, 使用默认构造
	current_event = event;
}

double QueueSystem::run() {    // 系统开始运行，不断消耗事件表，当消耗完成时结束运行
	this->init();
	while (current_event) {
		
		if (current_event->event_type == -1) {      //判断当前事件类型
			customerArrived();
		}
		else {
			customerDeparture();
		}
		delete current_event;
		
		current_event = event_list.dequeue();   //获得新事件
	};
	this->end();
	
	return (double)total_customer_stay_time / total_customer_num;   //返回顾客的平均逗留时间
}




void QueueSystem::end() {   // 系统运行结束，将所有服务窗口置空闲，并清空用户的等待队列和事件列表
	
	for (int i = 0; i != window_num; ++i) {      //设置所有窗口空闲
		windows[i].setIdle();
	}
	
	customer_list.clearQueue();   //顾客队列清空

	
	event_list.clearQueue();   //事件队列清空

}

int QueueSystem::getIdleServiceWindow() {
	for (int i = 0; i != window_num; ++i) {
		if (windows[i].isIdle()) {
			return i;
		}
	}
	return -1;
}


void QueueSystem::customerArrived() {     //处理用户到达事件

	total_customer_num++;
	int intertime = Random::getRandom(POISSON, 0.5);  //下一个顾客到达的时间间隔，我们假设100分钟内一定会出现一个顾客
														 
														 
	int time = current_event->occur_time + intertime;
	Event temp_event(time);

	
	if (time < total_service_time) {   //如果下一个顾客的到达时间小于服务的总时间，就把这个事件插入到事件列表中 同时将这个顾客加入到 customer_list 进行排队
		event_list.orderEnqueue(temp_event);
	} 


	 
	Customer *customer = new Customer(current_event->occur_time);   //处理当前的事件中到达的顾客
	if (!customer) {
		exit(-1);
	}
	customer_list.enqueue(*customer);


	int idleIndex = getIdleServiceWindow();
	if (idleIndex >= 0) {
		customer = customer_list.dequeue();
		windows[idleIndex].serveCustomer(*customer);
		windows[idleIndex].setBusy();

		
		Event temp_event(current_event->occur_time + customer->duration, idleIndex);
		event_list.orderEnqueue(temp_event);
	}
	delete customer;
}


void QueueSystem::customerDeparture() {
	
	if (current_event->occur_time < total_service_time) {
	
		total_customer_stay_time += current_event->occur_time - windows[current_event->event_type].getCustomerArriveTime();
		
		if (customer_list.length()) {
			Customer *customer;
			customer = customer_list.dequeue();
			windows[current_event->event_type].serveCustomer(*customer);

			
			Event temp_event(
				current_event->occur_time + customer->duration,
				current_event->event_type
			);
			event_list.orderEnqueue(temp_event);

			delete customer;
		}
		else {
			
			windows[current_event->event_type].setIdle();
		}

	}
}