#ifndef Node_h
#define Node_h

#include "Random.hpp"

#define RANDOM_PARAMETER 100

struct Node {
	int arrive_time;
	int duration;
	struct Node *next;

	
	Node(int arrive_time = 0,int duration = Random::getRandom(EXPONENTAIL, 0.1)) :  //Ĭ�ϵ����¼�Ϊ0����Ҫ������¼��������
		arrive_time(arrive_time),
		duration(duration),
		next(NULL) {}
};

typedef struct Node Node;
typedef struct Node Customer;

#endif 