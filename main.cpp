#include <iostream>
#include "myqueue.h"
#include <assert.h>
#include <stdlib.h>
#include <math.h>

#define poisson_arg 0.2 
#define num_of_queues 3
#define N 1000

double serve_time_gen(); // 2~8 s
double interval_gen();
double sys_time = 0;
double time_sum = 0;
class person{
public:
	person(unsigned n);
	unsigned No = 0;
	double interval;
	double arrive_time;
	double need_time;
	double waited_time = 0;
	double timetoserve;
	double begin_to_serve =0;
};
person::person(unsigned n): No(n) {
	timetoserve = need_time = serve_time_gen();
	interval = interval_gen();
}
int main(){
	Queue<unsigned> queue;
	srand((unsigned)time(NULL));
	person *p[N];
	for(int i=0; i< N; i++){
		p[i] = new person(i);
		p[i]->arrive_time = p[i]->interval + time_sum;
		time_sum += p[i]->interval;
	}
	int i=0;
	while(1){
		if(i == N) 
			break;
		if(queue.is_empty()){
			queue.enter_queue(i);
			sys_time = p[i]->arrive_time;
			p[i]->begin_to_serve = sys_time;
			i++;
		}
		else{
			int temp = queue.gettop();
			if(p[temp]->begin_to_serve == 0)
				p[temp]->begin_to_serve = sys_time;
			if(p[temp]->timetoserve < p[i]->arrive_time - sys_time){
				queue.de_queue();
				sys_time += p[temp]->timetoserve;
				p[temp]->timetoserve = 0;
			}
			else{
				p[temp]->timetoserve -= p[i]->arrive_time - sys_time;
				sys_time = p[i]->arrive_time;
				queue.enter_queue(i);
				i++;
			}
		}
	}
	while(!queue.is_empty()){
		int temp = queue.gettop();
		if(p[temp]->begin_to_serve == 0)
			p[temp]->begin_to_serve = sys_time;
		queue.de_queue();
		sys_time += p[temp]->timetoserve;
		p[temp]->timetoserve = 0;
	}
	double sum = 0;
	for(int i=0; i<N; i++){
		p[i]->waited_time = p[i]->begin_to_serve - p[i]->arrive_time;
		sum += p[i]->waited_time;
		assert(p[i]->timetoserve == 0);
	}
	std::cout << "average wait_time is " << sum/N;
	for(int i=0; i<N; i++)
		delete p[i];
}

double serve_time_gen(){
	return 4.0;
}
double interval_gen(){
#if 1
	double u = (double)rand()/RAND_MAX;
	return -log(1 - u) / poisson_arg;
#endif
}

