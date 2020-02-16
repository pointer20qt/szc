#include <iostream>
using namespace std;

class tool
{
public:
	int value;
	tool()
	{
		cout << "tool������" << endl;
	}
	tool(int value)
	{
		cout << "tool������������" << endl;
		this->value = value;
	}
	tool(const tool& other)
	{
		cout << "tool����������" << endl;
		value = other.value;
	}
	tool(const tool&& other) :value(other.value)
	{
		cout << "tool�ƶ�������" << endl;
	}
	~tool()
	{
		cout << "tool������" << endl;
	}
};

template<class T> class L_autoPtr
{
public:
	T* obj = nullptr;
	L_autoPtr() = default;
	L_autoPtr(T* t)
	{
		cout << "���캯��" << endl;
		obj = t;
	}
	L_autoPtr(L_autoPtr<T>& t)
	{
		cout << "�������캯��" << endl;
		obj = t.obj;
		t.obj = nullptr;//ת��ָ�����Ȩ
	}
	L_autoPtr& operator=(L_autoPtr<T>& t)
	{
		cout << "=���غ�������" << endl;
		delete obj;
		obj = t.obj;
		t.obj = nullptr;//ת��ָ�����Ȩ
		return *this;
	}
	T& operator*()
	{
		return *obj;
	}
	T* operator->()
	{
		return obj;
	}
	void reset(T* t)
	{
		cout << "�ͷ�ԭָ�룬�����ָ��" << endl;
		delete obj;
		obj = t;
	}
	T* release()
	{
		cout << "�ͷŶ������Ȩ������ָ��" << endl;
		T* temp = obj;
		obj = nullptr;
		return temp;
	}
	~L_autoPtr()
	{
		cout << "��������" << endl;
		delete obj;
	}
};

void main()
{
	L_autoPtr<tool> ptr(new tool(3));
	L_autoPtr<tool> ptr2(ptr);
	L_autoPtr<tool> ptr3;
	ptr3 = ptr2;
	cout << ptr3->value << endl;
	ptr3.reset(new tool(10));
	cout << ptr3->value << endl;
	L_autoPtr<tool> ptr4(ptr3.release());
	cout << (*ptr4).value << endl;
}

