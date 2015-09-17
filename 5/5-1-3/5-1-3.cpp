#include "iostream"
#include "stdlib.h"
#include "time.h"

#define CHECK_MAX 100000
double p;

double MakeRand(){
	double p1 = ((double)rand())/RAND_MAX * 1000000;
	return (p1-(int)p1);
}

int BLASED_RANDOM(){
	double p2 = MakeRand();
	if(p2 > p){
		return 0;
	}
	return 1;
}

int Half_Random(){
	while(1){
		int r1 = BLASED_RANDOM();
		int r2 = BLASED_RANDOM();
		if(r1 == 1 && r2 == 0){
			return 0;
		}else if(r1 == 0 && r2 == 1){
			return 1;
		}
	}
}

void system_init(){
	printf("system init...\n");
	srand(time(NULL));

	p = MakeRand();
	printf("init prob p:%lf\n",p);
}

void test_BLASED_RANDOM(){
	printf("run test prob p...\n");
	int sum = 0;
	for (int i = 0; i < CHECK_MAX; ++i)
	{
		sum += BLASED_RANDOM();
	}
	double p1 = (double)sum/CHECK_MAX;
	bool passed = (p1-p)<0.1 || (p1-p)>-0.1;
	printf("test %s!\n",(passed?"passed":"failed"));
	if(!passed){
		printf("error: checked prob p :%f\n",p1);
	}
}

void test_Half_Random(){
	printf("run test prob 0.5...\n");
	int sum = 0;
	for (int i = 0; i < CHECK_MAX; ++i)
	{
		sum += Half_Random();
	}
	double p1 = (double)sum/CHECK_MAX;
	bool passed = (p1-p)<0.1 || (p1-p)>-0.1;
	printf("test %s!\n",(passed?"passed":"failed"));
	if(!passed){
		printf("error: checked prob 0.5 :%f\n",p1);
	}
}

int main(int argc, char const *argv[])
{
	system_init();

	test_BLASED_RANDOM();
	
	test_Half_Random();

	return 0;
}
