//�˿��ŶӶ���

#ifndef Queue_hpp
#define Queue_hpp

#include <iostream>
#include <cstdlib>

#include "Event.hpp"

//��ͷ���Ķ���
template <typename T>    
class Queue
{
public:
	
	Queue() {           // ����һ����ͷ������ʽ���У��ڵ�λ�ڶ���β��
		this->front = new T;
		
		if (!this->front) { //����ڴ�����ʧ�ܣ���Ӧ�ü������г�����
			exit(-1);
		}
		// ��ʼ���ڵ�
		this->front->next = NULL;
		this->rear = this->front;
	}
	
	~Queue() {			//	����һ������ʱ����Ҫ�ͷŽڵ���������ڴ�
		this->clearQueue(); //��յ�ǰ�����е�Ԫ��
		delete this->front;  //ɾ��ͷ�ڵ�
		this->front = NULL;
		this->rear = NULL;
	}
	void clearQueue() {   //��ն���
		T *temp_node;

		while (this->front->next) {
			temp_node = this->front->next;
			this->front->next = temp_node->next;
			delete temp_node;
		}

		this->front->next = NULL;
		this->rear = this->front;
	}

	T* enqueue(T &node) {        // ���ʱ�����ݽڵ�ָ�룬�ⲿ���ݲ�Ӧ���ɴ�����й������Խ����ݿ���һ�ݣ�������ͷָ��
		T *new_node = new T;
		if (!new_node) {
			exit(-1);
		}
		*new_node = node;
		this->rear->next = new_node;
		this->rear = new_node;
		return this->front;
	}

	T* dequeue() {  //�Ӷ�ͷԪ�س���
		
		if (!this->front->next) {  //������пգ��򷵻ؿ�ָ��
			return NULL;
		}

		T *temp_node;
		temp_node = this->front->next;
		this->front->next = temp_node->next;


		if (this->rear == temp_node) {           // ���������ֻ��һ���ڵ㣬��ô�ǵý���β�ڵ�ָ����Ϊͷ���
			this->rear = this->front;
		}
		return temp_node;
	}

	T* orderEnqueue(Event &event) {   //�¼�ʱ��˳����룬�¼�������ķ����¼���Ӧ�ð��¼�˳����в���
		Event* temp = new Event;
		if (!temp) {
			exit(-1);
		}
		*temp = event;

		
		if (!this->front->next) {     // �������б���û���¼�, ��� temp �¼�����
			this->enqueue(*temp);
			return this->front;
		}

	
		Event *temp_event_list = this->front;      //��ʱ��˳�����
		
		//�������һ���¼�������һ���¼��ķ���ʱ��С��Ҫ�����ʱ���ʱ�䣬�������ָ�����
		while (temp_event_list->next && temp_event_list->next->occur_time < event.occur_time) {
			temp_event_list = temp_event_list->next;
		}

		//���¼����뵽������
		temp->next = temp_event_list->next;
		temp_event_list->next = temp;

		return this->front;   //���ض���ͷָ��
	}
	int  length() {
		T *temp_node;
		temp_node = this->front->next;
		int length = 0;
		while (temp_node) {
			temp_node = temp_node->next;
			++length;
		}
		return length;
	}
private:
	T * front;    //ͷ�ڵ�
	T *rear;   //��β
};



#endif 