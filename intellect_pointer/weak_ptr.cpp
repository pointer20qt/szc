#include<iostream>
#include<memory>
using namespace std;

//class tool
//{
//public:
//	int value;
//	tool()
//	{
//		cout << "tool������" << endl;
//	}
//	tool(int value)
//	{
//		cout << "tool������������" << endl;
//		this->value = value;
//	}
//	tool(const tool& other)
//	{
//		cout << "tool����������" << endl;
//		value = other.value;
//	}
//	tool(const tool&& other) :value(other.value)
//	{
//		cout << "tool�ƶ�������" << endl;
//	}
//	~tool()
//	{
//		cout << "tool������" << endl;
//	}
//};

template<class T> class Ref  //���ü�����
{
	int count = 0;  //ָ��ü��������share_ptrָ����
	T* object = nullptr; //��Ӧ�Ķ���
	int w_count = 0;  //ָ��ü��������weak_ptrָ����
public:
	Ref(T* target)  //���캯��
	{
		object = target;
		count++;
	}
	inline void increase()
	{
		count++;
	}
	inline void w_increase()
	{
		w_count++;
	}
	inline void decrease()
	{
		count--;
		if (count == 0) //�������Ϊ��
		{
			delete object;  //�ͷŸü��������Ӧ�Ķ���
			object = nullptr;
			if (w_count == 0)
			{
				delete this;  //�ͷŸü�������
			}
		}
	}
	inline void w_decrease()
	{
		w_count--;
		if (w_count == 0 && count == 0)//�������Ϊ��
		{
			delete this;  //�ͷŸü�������
		}
	}
	int getCount()  //��ȡָ��ü������������ָ����
	{
		return count;
	}
	T* getObject() //��ȡָ��ü��������Ӧ�Ķ���
	{
		return object;
	}
};

template<class T> class L_weakPtr;
template<class T> class L_sharedPtr  //shared_pPtr����ָ����
{
	friend class L_weakPtr<T>;
	Ref<T>* ref = nullptr;  //ָ���������ָ��
public:
	L_sharedPtr() = default;  //Ĭ�Ϲ��캯��
	L_sharedPtr(T* t)
	{
		cout << "L_sharedPtr������ָ�빹�캯��" << endl;
		ref = new Ref<T>(t);
	}
	L_sharedPtr(Ref<T>* t)
	{
		cout << "L_sharedPtr������Refָ�빹�캯��" << endl;
		ref = t;
		if (ref)
		{
			ref->increase();
		}
	}
	L_sharedPtr(const L_sharedPtr<T>& t)
	{
		cout << "L_sharedPtr���������캯��" << endl;
		ref = t.ref;
		if (ref)
		{
			ref->increase();
		}
	}
	L_sharedPtr(L_sharedPtr<T>&& t)
	{
		cout << "L_sharedPtr���ƶ����캯��" << endl;
		ref = t.ref;
		if (ref)
		{
			t.ref = nullptr;
		}
	}
	L_sharedPtr& operator=(L_sharedPtr<T>& t)
	{
		cout << "L_sharedPtr������=���غ���" << endl;
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
		cout << "L_sharedPtr���ƶ�=���غ���" << endl;
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
		cout << "L_sharedPtr������ref����" << endl;
		swap(ref, t.ref);
	}
	T& operator*()  //*���غ���
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
	T* operator->()  //->���غ���
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
		cout << "L_sharedPtr���滻������" << endl;
		if (ref)
		{
			ref->decrease();
		}
		if (t == nullptr) //����Ϊ��
		{
			ref = nullptr;
		}
		else  //����Ϊ��
		{
			ref = new Ref<T>(t);  //�½���һ��ref�������Ÿö���ĵ�ַ
		}
	}
	T* get()
	{
		cout << "L_sharedPtr�������ָ�뺯��" << endl;
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
		cout << "L_sharedPtr��������ü�������" << endl;
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
		cout << "L_sharedPtr���жϵ�ǰ�Ƿ�Ψһ����" << endl;
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
		cout << "L_sharedPtr���ж��Ƿ����������" << endl;
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
		cout << "shared_ptr����������" << endl;
		if (ref)
		{
			ref->decrease();
		}
	}
};

template<class T> class L_weakPtr  //weak_ptr����ָ����
{
	Ref<T>* ref = nullptr;  //ָ���������ָ��
public:
	L_weakPtr() = default;  //Ĭ�Ϲ��캯��
	L_weakPtr(L_sharedPtr<T>& t)
	{
		cout << "L_weakPtr������һ��shared_ptr���캯��" << endl;
		ref = t.ref;
		if (ref)
		{
			ref->w_increase();
		}
	}
	L_weakPtr(const L_weakPtr<T>& t)
	{
		cout << "L_weakPtr���������캯��" << endl;
		ref = t.ref;
		if (ref)
		{
			ref->w_increase();
		}
	}
	L_weakPtr(L_weakPtr<T>&& t)
	{
		cout << "L_weakPtr���ƶ����캯��" << endl;
		ref = t.ref;
		if (ref)
		{
			t.ref = nullptr;
		}
	}
	L_weakPtr& operator=(L_weakPtr<T>& t)
	{
		cout << "L_weakPtr������=���غ���" << endl;
		if (ref)
		{
			ref->w_decrease();
		}
		ref = t.ref;
		if (ref)
		{
			ref->w_increase();
		}
		return *this;
	}
	L_weakPtr& operator=(L_weakPtr<T>&& t)
	{
		cout << "L_weakPtr���ƶ�=���غ���" << endl;
		if (ref)
		{
			ref->w_decrease();
		}
		ref = t.ref;
		if (ref)
		{
			t.ref = nullptr;
		}
		return *this;
	}
	void swap(L_weakPtr<T>& t)
	{
		cout << "L_weakPtr������ref����" << endl;
		swap(ref, t.ref);
	}
	void reset()
	{
		cout << "L_weakPtr���ͷ�ref����" << endl;
		if (ref)
		{
			ref->w_decrease();
		}		
		ref = nullptr;
	}
	int use_count()
	{
		cout << "L_weakPtr��������ü�������" << endl;
		if (ref)
		{
			return ref->getCount();
		}
		else
		{
			return 0;
		}
	}
	L_sharedPtr<T>& lock()
	{
		cout << "L_weakPtr�����һ��shared_ptr" << endl;
		L_sharedPtr<T> temp(ref);
		return temp;
	}
	bool expired()
	{
		cout << "L_weakPtr���ж��Ƿ��Ѿ�ɾ��" << endl;
		if (ref)
		{
			return ref->getCount() > 0 ? true : false;
		}
		else
		{
			return false;
		}
	}
}; 

class node
{
public:
	L_weakPtr<node> pre;
	L_weakPtr<node> next;
	~node()
	{
		cout << "node��������" << endl;
	}
};

void main()
{
	L_sharedPtr<node> node1(new node);
	L_sharedPtr<node> node2(new node);
	node1->next.operator=(node2);
	node2->pre.operator=(node1);
}


