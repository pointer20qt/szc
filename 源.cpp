#include <iostream>
#include <vector>
#include <Initializer_list>
//#define NDEBUG 
#include <assert.h>
//#include "test.h"
//#include "text.h"
using namespace std;

class vec
{
public:
	vector<int> obj;
	vec() = default;
	vec(std::initializer_list<int> arry)
	{
		cout << "��ʼ���б�����" << endl;
		for (auto i = arry.begin(); i != arry.end(); i++)
		{
			obj.push_back(*i);
		}
	}
	vec(const vec& vc) :obj(vc.obj)
	{
		cout << "����������" << endl;
	}
	int& operator[](int index)
	{
		assert(index >= 0 && index < obj.size());
		return obj[index];
	}
	~vec()
	{
		cout << "������" << endl;
	}
}; 


void main()
{
	vec v{ 1, 2, 3, 4, 5, 6 };
	cout << v[3] << endl;
	v[2] = 10;
	vec v2(v);
	cout << v2[2] << endl;
	const int i = 3;
	static_assert(i != 2, "����");
}