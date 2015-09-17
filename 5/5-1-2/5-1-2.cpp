#include <iostream>

#define CHECK_MAX 100000
using namespace std;

double MakeRand(){
	double p1 = ((double)rand())/RAND_MAX * 1000000;
	return (p1-(int)p1);
}

int Radnom_0_1(){
	double p2 = MakeRand();
	if(p2 >= 0.5){
		return 0;
	}
	return 1;
}

int Radnom_a_b(int a, int b){
	if(a>b){
		//error
		return -1;
	}
	int length = b-a;
	int length_temp = length;
	int num = 0;
	while (length>0){
		num ++;
		length>>=1;
	}

	int sum;
	do{
		sum = 0;
		for (int i = 0; i < num; ++i)
		{
			sum = (sum<<1) + Radnom_0_1();
		}
	}while(sum>length_temp);
	return sum+a;
}

void system_init(){
	printf("system init...\n");
	srand(time(NULL));
}

void test_random_0_1(){
	printf("run test random(0,1)...\n");
	int numbers[2] = {0};
	for (int i = 0; i < CHECK_MAX; ++i)
	{
		numbers[Radnom_0_1()]++;
	}
	double p_0 = (double)numbers[0]/CHECK_MAX;
	double p_1 = (double)numbers[1]/CHECK_MAX;
	bool passed = ((p_1-p_0)<0.1 || (p_1-p_0)>-0.1) && ((p_0 + p_1 - 1)<0.1 || (p_0 + p_1 - 1)>-0.1);
	printf("test %s!\n",(passed?"passed":"failed"));
	if(!passed){
		printf("error: prob 0 :%f\n",p_0);
		printf("error: prob 1 :%f\n",p_1);
	}
}

void init_a_b(int *a, int *b){
	printf("start init a,b...\n");
	do{
		*a = rand();
		*b = rand();
	}while(*a>*b);
}

void test_random_a_b(){
	printf("run test random(a,b)...\n");
	int a,b;
	init_a_b(&a,&b);
	//printf ("a:%d,b:%d\n",a,b);
	int numbers_a_b[b-a+1];
	for (int i = 0; i < b-a+1; ++i)
	{
		numbers_a_b[i] = 0;
	}
	for (int i = 0; i < CHECK_MAX; ++i)
	{
		numbers_a_b[Radnom_a_b(a,b)-a]++;
	}
	double p = 1.0/(b-a+1);
	for (int i = 0; i < b-a+1; ++i)
	{
		double p_i = numbers_a_b[i]/(double)CHECK_MAX;
		if(p_i-p>0.1 || p-p_i>0.1){
			printf("test failed!\n");
			printf("error: i:%d p_i:%f p:%f\n",i+a,p_i,p);
			return;
		}
	}
	printf("test passed!\n");
}

int main(int argc, char const *argv[])
{
	system_init();

	test_random_0_1();

	test_random_a_b();

	return 0;
}
