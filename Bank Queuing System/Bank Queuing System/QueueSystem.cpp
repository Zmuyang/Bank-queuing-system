#include "QueueSystem.hpp"
#include "Random.hpp"
#include "Event.hpp"

QueueSystem::QueueSystem(int total_service_time, int window_num) :
	total_service_time(total_service_time),
	window_num(window_num),
	total_customer_stay_time(0),
	total_customer_num(0) {
	this->windows = new ServiceWindow[window_num];   //�������񴰿�
}
QueueSystem::~QueueSystem() {
	delete[] windows;
}
void QueueSystem::simulate(int simulate_num) {
	double sum = 0;
	for (int i = 0; i != simulate_num; ++i) {
		sum += run();  // ÿһ�����У����Ƕ�Ҫ��������һ��ģ���У��˿Ͷ����˶��
	}
	avg_stay_time = (double)sum / simulate_num;    //����ƽ������ʱ��
	avg_customers = (double)total_customer_num / (total_service_time*simulate_num);  //����ÿ����ƽ���˿���
}

void QueueSystem::init() {      // ϵͳ��������, ��ʼ���¼�����, �����һ���¼�

	Event *event = new Event;  // ��һ���¼��϶��ǵ����¼�, ʹ��Ĭ�Ϲ���
	current_event = event;
}

double QueueSystem::run() {    // ϵͳ��ʼ���У����������¼������������ʱ��������
	this->init();
	while (current_event) {
		
		if (current_event->event_type == -1) {      //�жϵ�ǰ�¼�����
			customerArrived();
		}
		else {
			customerDeparture();
		}
		delete current_event;
		
		current_event = event_list.dequeue();   //������¼�
	};
	this->end();
	
	return (double)total_customer_stay_time / total_customer_num;   //���ع˿͵�ƽ������ʱ��
}




void QueueSystem::end() {   // ϵͳ���н����������з��񴰿��ÿ��У�������û��ĵȴ����к��¼��б�
	
	for (int i = 0; i != window_num; ++i) {      //�������д��ڿ���
		windows[i].setIdle();
	}
	
	customer_list.clearQueue();   //�˿Ͷ������

	
	event_list.clearQueue();   //�¼��������

}

int QueueSystem::getIdleServiceWindow() {
	for (int i = 0; i != window_num; ++i) {
		if (windows[i].isIdle()) {
			return i;
		}
	}
	return -1;
}


void QueueSystem::customerArrived() {     //�����û������¼�

	total_customer_num++;
	int intertime = Random::getRandom(POISSON, 0.5);  //��һ���˿͵����ʱ���������Ǽ���100������һ�������һ���˿�
														 
														 
	int time = current_event->occur_time + intertime;
	Event temp_event(time);

	
	if (time < total_service_time) {   //�����һ���˿͵ĵ���ʱ��С�ڷ������ʱ�䣬�Ͱ�����¼����뵽�¼��б��� ͬʱ������˿ͼ��뵽 customer_list �����Ŷ�
		event_list.orderEnqueue(temp_event);
	} 


	 
	Customer *customer = new Customer(current_event->occur_time);   //����ǰ���¼��е���Ĺ˿�
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