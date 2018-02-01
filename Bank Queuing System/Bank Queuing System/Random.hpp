
#ifndef Random_hpp
#define Random_hpp

#include <cstdlib>
#include <cmath>

enum RandomType {
	UNIFORM,
	EXPONENTAIL,
	POISSON,
};

class Random {
public:
	static double getRandom(RandomType type, double parameter) {
		switch (type) {
		case UNIFORM:
			return uniform(parameter);
			break;
		case EXPONENTAIL:
			return exponentail(parameter);
		case POISSON:
			return poisson(parameter);
		default:
			return 0;
			break;
		}
	}
	
	static double uniform(double max = 1) {      //0-1֮����Ӿ��ȷֲ������ֵ
		return ((double)std::rand() / (RAND_MAX))*max;   //RAND_MAX �� <stdlib.h> ��α��������ɺ��� rand ���ܷ��ص������ֵ
	}
	
	static double exponentail(double lambda) {
		return -log(1 - uniform()) / lambda;
	}
	
	static double poisson(double lambda) {
		int t = 0;
		double p = exp(-lambda);
		double f = p;
		double u = uniform();
		while (true) {
			if (f > u)
				break;
			t++;
			p = p * lambda / t;
			f += p;
		}
		return t;
	}
};

#endif 