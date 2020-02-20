#include <iostream>
#include <math.h>
#include <time.h>
using namespace std;




//rand()从随机数序列中取下一个    srand(time(0)) 初始化随机数序列

int run1(int a, int b)  //生成[a, b)的随机数
{
	int t = rand() % (b - a) + a;
	return t;
}

int run2(int a, int b)  //生成[a, b]的随机数
{
	int t = rand() % (b - a + 1) + a;
	return t;
}

int run3(int a, int b)  //生成(a, b]的随机数
{
	int t = rand() % (b - a) + a + 1;
	return t;
}

bool run()  //生成一个0~1的随机小数double
{
	double t = rand() / (double)RAND_MAX;
	if (t >= 0 && t <= 1)
	{
		cout << t << endl;
		return true;
	}
	else
	{
		cout << t << endl;
		return false;
	}
}

bool run(int a,int b)//怎么生成a~b的随机小数
{
	double t = (rand() / (double)RAND_MAX) * (b - a) + a;
	if (t >= a && t <= b)
	{
		cout << t << endl;
		return true;
	}
	else
	{
		cout << t << endl;
		return false;
	}
}

bool run(int n)//传入0到100的整数n，概率性判断成功,成功返回true
{
	int t = rand() % 100;
	if (t < n)
	{
		cout << t << endl;
		return true;
	}
	else
	{
		cout << t << endl;
		return false;
	}
}

bool run(double n)//传入0到1的double n，概率性判断成功，成功返回ture。
{
	double t = rand() / (double)(RAND_MAX);
	if (t < n)
	{
		cout << t << endl;
		return true;
	}
	else
	{
		cout << t << endl;
		return false;
	}
}

void main()
{
	srand(time(0));
	int t = 0;
	int f = 0;
	for (int i = 0; i < 100; i++)
	{
		if (run(0.6))
		{
			t++;
		}
		else
		{
			f++;
		}
	}
	cout << "t:" << t << " f:" << f << endl;
	for (int i = 0; i < 100; i++)
	{
		cout << run1(5, 10) << endl;
	}
	run2(3, 7);
	run3(1, 8);
}