//顾客排队队列

#ifndef Queue_hpp
#define Queue_hpp

#include <iostream>
#include <cstdlib>

#include "Event.hpp"

//带头结点的队列
template <typename T>    
class Queue
{
public:
	
	Queue() {           // 构造一个带头结点的链式队列，节点位于队列尾部
		this->front = new T;
		
		if (!this->front) { //如果内存申请失败，则不应该继续运行程序了
			exit(-1);
		}
		// 初始化节点
		this->front->next = NULL;
		this->rear = this->front;
	}
	
	~Queue() {			//	销毁一个队列时候需要释放节点中申请的内存
		this->clearQueue(); //清空当前队列中的元素
		delete this->front;  //删除头节点
		this->front = NULL;
		this->rear = NULL;
	}
	void clearQueue() {   //清空队列
		T *temp_node;

		while (this->front->next) {
			temp_node = this->front->next;
			this->front->next = temp_node->next;
			delete temp_node;
		}

		this->front->next = NULL;
		this->rear = this->front;
	}

	T* enqueue(T &node) {        // 入队时，传递节点指针，外部数据不应该由此类进行管理，所以将数据拷贝一份，并返回头指针
		T *new_node = new T;
		if (!new_node) {
			exit(-1);
		}
		*new_node = node;
		this->rear->next = new_node;
		this->rear = new_node;
		return this->front;
	}

	T* dequeue() {  //从对头元素出队
		
		if (!this->front->next) {  //如果队列空，则返回空指针
			return NULL;
		}

		T *temp_node;
		temp_node = this->front->next;
		this->front->next = temp_node->next;


		if (this->rear == temp_node) {           // 如果队列中只有一个节点，那么记得将队尾节点指针置为头结点
			this->rear = this->front;
		}
		return temp_node;
	}

	T* orderEnqueue(Event &event) {   //事件时的顺序插入，事件有自身的发生事件，应该按事件顺序进行插入
		Event* temp = new Event;
		if (!temp) {
			exit(-1);
		}
		*temp = event;

		
		if (!this->front->next) {     // 如果这个列表里没有事件, 则把 temp 事件插入
			this->enqueue(*temp);
			return this->front;
		}

	
		Event *temp_event_list = this->front;      //按时间顺序插入
		
		//如果有下一个事件，且下一个事件的发生时间小于要插入的时间的时间，则继续将指针后移
		while (temp_event_list->next && temp_event_list->next->occur_time < event.occur_time) {
			temp_event_list = temp_event_list->next;
		}

		//将事件插入到队列中
		temp->next = temp_event_list->next;
		temp_event_list->next = temp;

		return this->front;   //返回队列头指针
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
	T * front;    //头节点
	T *rear;   //队尾
};



#endif 