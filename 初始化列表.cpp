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
		cout << "��ʼ���б�����" << endl;
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
		cout << "����������" << endl;
		this->obj = vc.obj;
	}
	int operator[](int index)
	{
		return obj[index];
	}
	~vec()
	{
		cout << "������" << endl;
	}
}; 


void main()
{
	vec v = { 1, 2, 3, 4, 5, 6 };
	cout << v[3] << endl;
	vec v2(v);
}