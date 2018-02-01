/*
	维护一个事件列表，当一个事件发生时，通知队列系统更新它自身的状态
*/
#ifndef Event_hpp
#define Event_hpp

#include "Random.hpp"

struct Event {
	int occur_time;

	int event_type;   //-1表示到达事件，>=0表示离开事件，同时数值表示所离开的服务窗口

	Event* next;


	Event(int occur_time = Random::getRandom(POISSON, 0.5),int event_type = -1) :     //默认为到达事件
		occur_time(occur_time),
		event_type(event_type),
		next(NULL) {}
};

#endif 