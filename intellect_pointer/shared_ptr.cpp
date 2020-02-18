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


template<class T> class Ref  //���ü�����
{
	int count = 0;  //ָ��ü������������ָ����
	T* object = nullptr; //��Ӧ�Ķ���
public:
	Ref(T* target)//���캯��
	{
		object = target;
		count++;
	}
	inline void increase()
	{
		count++;
	}
	inline void decrease()
	{
		count--;
		if (count == 0) //�������Ϊ��
		{
			delete object;  //�ͷŸü��������Ӧ�Ķ���
			delete this;  //�ͷŸü�������
		}
	}
	int getCount()  //��ȡָ��ü������������ָ����
	{
		return count;
	}
	T* getObject()//��ȡָ��ü��������Ӧ�Ķ���
	{
		return object;
	}
};

template<class T> class L_sharedPtr  //����ָ����
{
	Ref<T>* ref = nullptr;  //ָ���������ָ��
public:
	L_sharedPtr() = default;  //Ĭ�Ϲ��캯��
	L_sharedPtr(T* t)
	{
		cout << "����ָ�빹�캯��" << endl;
		ref = new Ref<T>(t);
	}
	L_sharedPtr(const L_sharedPtr<T>& t)
	{
		cout << "�������캯��" << endl;
		ref = t.ref;
		if (ref)
		{
			ref->increase();
		}
	}
	L_sharedPtr(L_sharedPtr<T>&& t)
	{
		cout << "�ƶ����캯��" << endl;
		ref = t.ref;
		if (ref)
		{
			t.ref = nullptr;
		}
	}
	L_sharedPtr& operator=(L_sharedPtr<T>& t)
	{
		cout << "����=���غ���" << endl;
		if (ref)
		{
			ref->decrease();
		}
		ref = t.ref;
		if (ref)
		{
			ref->increase();
		}
		return *this;
	}
	L_sharedPtr& operator=(L_sharedPtr<T>&& t)
	{
		cout << "�ƶ�=���غ���" << endl;
		if (ref)
		{
			ref->decrease();
		}
		ref = t.ref;
		if (ref)
		{
			t.ref = nullptr;
		}
		return *this;
	}
	void swap(L_sharedPtr<T>& t)
	{
		cout << "����ref����" << endl;
		swap(ref, t.ref);
	}
	T& operator*()
	{
		if (ref)
		{
			return *(ref->getObject());
		}
		else
		{
			return *(T*)nullptr;
		}
	}
	T* operator->()
	{
		if (ref)
		{
			return ref->getObject();
		}
		else
		{
			return (T*)nullptr;
		}
	}
	void reset(T* t = nullptr)
	{
		cout << "�滻������" << endl;
		if (ref)
		{
			ref->decrease();
		}
		if (t == nullptr) //����Ϊ��
		{
			ref = nullptr;
		}
		else//����Ϊ��
		{
			ref = new Ref<T>(t);  //�½���һ��ref�������Ÿö���ĵ�ַ
		}
	}
	T* get()
	{
		cout << "�����ָ�뺯��" << endl;
		if (ref)
		{
			return ref->getObject();
		}
		else
		{
			return (T*)nullptr;
		}
	}
	int use_count()
	{
		cout << "������ü�������" << endl;
		if (ref)
		{
			return ref->getCount();
		}
		else
		{
			return 0;
		}
	}
	bool unique()
	{
		cout << "�жϵ�ǰ�Ƿ�Ψһ����" << endl;
		if (ref)
		{
			return ref->getCount() == 1 ? true : false;
		}
		else
		{
			return false;
		}
	}
	operator bool()
	{
		cout << "�ж��Ƿ����������" << endl;
		if (ref)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	~L_sharedPtr()
	{
		cout << "����ָ����������" << endl;
		if (ref)
		{
			ref->decrease();
		}
	}
};

void main()
{
	L_sharedPtr<tool> ptr(new tool(3));
	cout << (*ptr).value << endl;
	//��������ptr2��ptr.obj,ptr2.obj��ָ��new tool(3)
	L_sharedPtr<tool> ptr2(ptr);
	cout << (*ptr2).value << endl;
	L_sharedPtr<tool> ptr3;
	//��ֵptr3,ptr2.ptr3.obj,ptr2.obj��ָ��new tool(3)
	ptr3 = ptr2;
	cout << ptr->value << endl;
	cout << ptr2->value << endl;
	cout << ptr3->value << endl;
	//�ͷ�new tool(3),��ptr3.obj���·���ռ�
	ptr3.reset(new tool(10));
	cout << (*ptr).value << endl;
	cout << (*ptr2).value << endl;
	cout << (*ptr3).value << endl;
	//�ƶ�����ptr4,ptr3.obj=nullptr,
	//��ptr3ԭ��ָ��Ŀռ��ַ����ptr4
	L_sharedPtr<tool> ptr4(std::move(ptr3));
	cout << ptr4->value << endl;
}

