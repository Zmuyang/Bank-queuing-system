/*
	������������ϵͳ��ģ��
*/
#ifndef QueueSystem_hpp
#define QueueSystem_hpp

#include "Event.hpp"
#include "Queue.hpp"
#include "ServiceWindow.hpp"

class QueueSystem {

public:

	QueueSystem(int total_service_time, int window_num);   //��ʼ������ϵͳ


	~QueueSystem();   //����


	void simulate(int simulate_num);   //����ģ��

	inline double getAvgStayTime() {
		return avg_stay_time;   //ƽ������ʱ��
	}
	inline double getAvgCustomers() {
		return avg_customers;   //ÿ����ƽ���˿���
	}

private:
	
	double run();   //����ϵͳ����һ��

	
	void init();   //��ʼ�����ֲ���


	void end();  //��ո��ֲ���

	
	int getIdleServiceWindow();   //��ÿ��д�������

	
	void customerArrived();   //����˿͵����¼�

	
	void customerDeparture();  //����˿��뿪�¼�

	
	int window_num;   //���񴰿ڵ�����

	 
	int total_service_time;   //�ܵķ���ʱ��

	
	int total_customer_stay_time;   //�ܵĶ���ʱ��

	
	int total_customer_num;  //�ܹ˿���

	//62-65 ���ĳ�Ա
	ServiceWindow*  windows;
	Queue<Customer> customer_list;
	Queue<Event>       event_list;
	Event*          current_event;

	//���ⲿ���õĽ��
	double avg_customers;
	double avg_stay_time;

};


#endif 