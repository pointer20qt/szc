#include <iostream>
#include <Initializer_list>
//#include "test.h"
//#include "text.h"
using namespace std;

class vec
{
public:
	int* obj;
	vec() = default;
	vec(std::initializer_list<int> arry)
	{
		cout << "初始化列表构造了" << endl;
		obj = new int[arry.size()];
		int j = 0;
		for (auto i = arry.begin(); i != arry.end(); i++)
		{
			*(obj + j) = *i;
			j++;
		}
	}
	vec(const vec& vc) 
	{
		cout << "拷贝构造了" << endl;
		this->obj = vc.obj;
	}
	int operator[](int index)
	{
		return obj[index];
	}
	~vec()
	{
		cout << "析构了" << endl;
	}
}; 


void main()
{
	vec v = { 1, 2, 3, 4, 5, 6 };
	cout << v[3] << endl;
	vec v2(v);
}