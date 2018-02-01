#include "QueueSystem.hpp"

#include <iostream>

#include <cstdlib>
#include <time.h>   //windows下调取系统时间头文件

int main() {
#ifdef __APPLE__
	std::srand((unsigned)std::time(0));   //使用当前时间作为随机数种子
#else
	std::srand(time(0));
#endif
	int total_service_time = 240;   //按分钟计算
	int window_num = 4;
	int simulate_num = 100000;  //模拟次数

	QueueSystem system(total_service_time, window_num);
	system.simulate(simulate_num);

	std::cout << "The average time of customer stay in bank: "
		<< system.getAvgStayTime() << std::endl;
	std::cout << "The number of customer arrive bank per minute: " << system.getAvgCustomers() << std::endl;

	return 0;
}