/*
队列系统的服务窗口对象，每当一个银行创建时，服务窗口会被创建，为了让整个问题更加灵活，我们假设需要创建 window_num 个窗口
*/

#ifndef ServiceWindow_hpp
#define ServiceWindow_hpp

#include "Node.hpp"

enum WindowStatus {
	SERVICE,   //被占用
	IDLE,     //空闲
};

class ServiceWindow {
public:
	inline ServiceWindow() {
		window_status = IDLE;
	};
	inline bool isIdle() const {
		if (window_status == IDLE) {
			return true;
		}
		else {
			return false;
		}
	}
	inline void serveCustomer(Customer &customer) {
		this->customer = customer;
	}
	inline void setBusy() {
		window_status = SERVICE;
	}
	inline void setIdle() {
		window_status = IDLE;
	}
	inline int getCustomerArriveTime() const {
		return customer.arrive_time;
	}
	inline int getCustomerDuration() const {
		return customer.duration;
	}
private:
	Customer customer;
	WindowStatus window_status;
};

#endif 