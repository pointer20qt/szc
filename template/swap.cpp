#include <iostream>
//#include <vector>
using namespace std;


template<class T> void Lswap(T& a, T& b)
{
	cout << "ģ�庯��Lswap" << endl;
	T temp(a);
	temp = a;
	a = b;
	b = temp;	
}

template<class T, class T2> T Lmax(T a, T2 b)
{
	cout << "ģ�庯��Lmax" << endl;
	return a > b ? a : b;
}

int Lmax(int a, double b)
{
	cout << "��ͨ����Lmax" << endl;
	return a > b ? a : b;
}

class student
{
public:
	int num;
	char* name;
	student(int num,char* name)
	{
		cout << "���캯��" << endl;
		this->num = num;
		this->name = new char(*name);
	}
	student(const student& other)
	{
		cout << "�������캯��" << endl;
		this->num = other.num;
		this->name = new char(*(other.name));
	}
	student& operator=(const student& other)
	{
		cout << "=���غ���" << endl;
		this->num = other.num;
		delete this->name;
		this->name = new char(*(other.name));
		return *this;
	}
	~student()
	{
		cout << "��������" << endl;
		delete name;
	}
};

void main()
{
	int x1 = 5, x2 = 8;
	double d1 = 4.3, d2 = 7.5;
	student a1(101, "zl"), a2(102, "wm");
	Lswap(x1, x2);
	Lswap(d1, d2);
	Lswap(a1, a2);
	//��ʽ�Ƶ�
	cout << a1.num << "�Զ������ͽ�������" << a2.num << endl;
	cout << x1 << "int���ͽ�������" << x2 << endl;
	cout << d1 << "double���ͽ�������" << d2 << endl;

	//��ʽ�Ƶ�
	cout << Lmax<int>(x2, d1) << endl;
	//��ʽָ��ģ��
	cout << Lmax(x1, d1) << endl;//������ͨ����
	cout << Lmax<>(x1, d1) << endl;//����ģ�庯��
}