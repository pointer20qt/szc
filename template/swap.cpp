#include <iostream>
//#include <vector>
using namespace std;


template<class T> void Lswap(T& a, T& b)
{
	cout << "模板函数Lswap" << endl;
	T temp(a);
	temp = a;
	a = b;
	b = temp;	
}

template<class T, class T2> T Lmax(T a, T2 b)
{
	cout << "模板函数Lmax" << endl;
	return a > b ? a : b;
}

int Lmax(int a, double b)
{
	cout << "普通函数Lmax" << endl;
	return a > b ? a : b;
}

class student
{
public:
	int num;
	char* name;
	student(int num,char* name)
	{
		cout << "构造函数" << endl;
		this->num = num;
		this->name = new char(*name);
	}
	student(const student& other)
	{
		cout << "拷贝构造函数" << endl;
		this->num = other.num;
		this->name = new char(*(other.name));
	}
	student& operator=(const student& other)
	{
		cout << "=重载函数" << endl;
		this->num = other.num;
		delete this->name;
		this->name = new char(*(other.name));
		return *this;
	}
	~student()
	{
		cout << "析构函数" << endl;
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
	//隐式推导
	cout << a1.num << "自定义类型交换函数" << a2.num << endl;
	cout << x1 << "int类型交换函数" << x2 << endl;
	cout << d1 << "double类型交换函数" << d2 << endl;

	//显式推导
	cout << Lmax<int>(x2, d1) << endl;
	//显式指定模板
	cout << Lmax(x1, d1) << endl;//调用普通函数
	cout << Lmax<>(x1, d1) << endl;//调用模板函数
}