#include "iostream"
#include "stdlib.h"
#include "time.h"
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

int main(int argc, char const *argv[])
{
	printf("system init...\n");
	srand(time(NULL));

	p = MakeRand();
	printf("init prob p:%lf\n",p);

	printf("check prob p...");
	int CHECK_MAX = 100000;
	int sum = 0;
	for (int i = 0; i < CHECK_MAX; ++i)
	{
		sum += BLASED_RANDOM();
	}
	printf("checked prob p :%f\n",(double)sum/CHECK_MAX);

	printf("check prob 0.5...");
	sum = 0;
	for (int i = 0; i < CHECK_MAX; ++i)
	{
		sum += Half_Random();
	}
	printf("checked prob 0.5 :%f\n",(double)sum/CHECK_MAX);
	
	return 0;
}
