#include <iostream>
#include <vector>
#include <memory>
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


template<class T> class L_uniquePtr  //����ָ����
{
public:
	T* obj = nullptr;
	L_uniquePtr() = default;  //Ĭ�Ϲ��캯��
	L_uniquePtr(T* t)
	{
		cout << "���캯��" << endl;
		obj = t;
	}
	L_uniquePtr(const L_uniquePtr<T>& t) = delete; //�������캯����ɾ��
	L_uniquePtr(L_uniquePtr<T>&& t)
	{
		cout << "�ƶ����캯��" << endl;
		obj = t.obj;
		t.obj = nullptr;  //ת��ָ�����Ȩ
	}
	L_uniquePtr& operator=(L_uniquePtr<T>& t) = delete; //����=���غ�����ɾ��
	L_uniquePtr& operator=(L_uniquePtr<T>&& t)
	{
		cout << "�ƶ�=���غ���" << endl;
		obj = t.release();
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
	T* get(){
		return obj;
	}
	~L_uniquePtr()
	{
		cout << "��������" << endl;
		delete obj;
	}
};
void main()
{
	L_uniquePtr<tool> ptr(new tool(3));
	cout << (*ptr).value << endl;
	L_uniquePtr<tool> ptr2(std::move(ptr));  //�ƶ�����ptr2��ptr.obj=nullptr
	cout << (*ptr2).value << endl;
	L_uniquePtr<tool> ptr3;
	ptr3 = std::move(ptr2);   //��ֵptr3,ptr2.obj=nullptr
	cout << ptr3->value << endl;
	ptr3.reset(new tool(10));  //�ͷ�new tool(3),��ptr3.obj���·���ռ�
	cout << (*ptr3).value << endl;
	L_uniquePtr<tool> ptr4(std::move(ptr3.release()));  //ptr3.obj=nullptr,��ptr3ԭ��ָ��Ŀռ��ַ����ptr4
	cout << ptr4->value << endl;
}
