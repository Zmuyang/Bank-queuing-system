/*
	ά��һ���¼��б���һ���¼�����ʱ��֪ͨ����ϵͳ�����������״̬
*/
#ifndef Event_hpp
#define Event_hpp

#include "Random.hpp"

struct Event {
	int occur_time;

	int event_type;   //-1��ʾ�����¼���>=0��ʾ�뿪�¼���ͬʱ��ֵ��ʾ���뿪�ķ��񴰿�

	Event* next;


	Event(int occur_time = Random::getRandom(POISSON, 0.5),int event_type = -1) :     //Ĭ��Ϊ�����¼�
		occur_time(occur_time),
		event_type(event_type),
		next(NULL) {}
};

#endif 