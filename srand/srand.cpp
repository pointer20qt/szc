#include <iostream>
#include <math.h>
#include <time.h>
using namespace std;




//rand()�������������ȡ��һ��    srand(time(0)) ��ʼ�����������

int run1(int a, int b)  //����[a, b)�������
{
	int t = rand() % (b - a) + a;
	return t;
}

int run2(int a, int b)  //����[a, b]�������
{
	int t = rand() % (b - a + 1) + a;
	return t;
}

int run3(int a, int b)  //����(a, b]�������
{
	int t = rand() % (b - a) + a + 1;
	return t;
}

bool run()  //����һ��0~1�����С��double
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

bool run(int a,int b)//��ô����a~b�����С��
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

bool run(int n)//����0��100������n���������жϳɹ�,�ɹ�����true
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

bool run(double n)//����0��1��double n���������жϳɹ����ɹ�����ture��
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