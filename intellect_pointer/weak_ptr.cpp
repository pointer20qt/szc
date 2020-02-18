#include<iostream>
#include<memory>
using namespace std;

//class tool
//{
//public:
//	int value;
//	tool()
//	{
//		cout << "tool构造了" << endl;
//	}
//	tool(int value)
//	{
//		cout << "tool单参数构造了" << endl;
//		this->value = value;
//	}
//	tool(const tool& other)
//	{
//		cout << "tool拷贝构造了" << endl;
//		value = other.value;
//	}
//	tool(const tool&& other) :value(other.value)
//	{
//		cout << "tool移动构造了" << endl;
//	}
//	~tool()
//	{
//		cout << "tool析构了" << endl;
//	}
//};

template<class T> class Ref  //引用计数类
{
	int count = 0;  //指向该计数对象的share_ptr指针数
	T* object = nullptr; //对应的对象
	int w_count = 0;  //指向该计数对象的weak_ptr指针数
public:
	Ref(T* target)  //构造函数
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
		if (count == 0) //如果计数为零
		{
			delete object;  //释放该计数对象对应的对象
			object = nullptr;
			if (w_count == 0)
			{
				delete this;  //释放该计数对象
			}
		}
	}
	inline void w_decrease()
	{
		w_count--;
		if (w_count == 0 && count == 0)//如果计数为零
		{
			delete this;  //释放该计数对象
		}
	}
	int getCount()  //获取指向该计数对象的智能指针数
	{
		return count;
	}
	T* getObject() //获取指向该计数对象对应的对象
	{
		return object;
	}
};

template<class T> class L_weakPtr;
template<class T> class L_sharedPtr  //shared_pPtr智能指针类
{
	friend class L_weakPtr<T>;
	Ref<T>* ref = nullptr;  //指向技术对象的指针
public:
	L_sharedPtr() = default;  //默认构造函数
	L_sharedPtr(T* t)
	{
		cout << "L_sharedPtr：传递指针构造函数" << endl;
		ref = new Ref<T>(t);
	}
	L_sharedPtr(Ref<T>* t)
	{
		cout << "L_sharedPtr：传递Ref指针构造函数" << endl;
		ref = t;
		if (ref)
		{
			ref->increase();
		}
	}
	L_sharedPtr(const L_sharedPtr<T>& t)
	{
		cout << "L_sharedPtr：拷贝构造函数" << endl;
		ref = t.ref;
		if (ref)
		{
			ref->increase();
		}
	}
	L_sharedPtr(L_sharedPtr<T>&& t)
	{
		cout << "L_sharedPtr：移动构造函数" << endl;
		ref = t.ref;
		if (ref)
		{
			t.ref = nullptr;
		}
	}
	L_sharedPtr& operator=(L_sharedPtr<T>& t)
	{
		cout << "L_sharedPtr：拷贝=重载函数" << endl;
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
		cout << "L_sharedPtr：移动=重载函数" << endl;
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
		cout << "L_sharedPtr：交换ref函数" << endl;
		swap(ref, t.ref);
	}
	T& operator*()  //*重载函数
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
	T* operator->()  //->重载函数
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
		cout << "L_sharedPtr：替换对象函数" << endl;
		if (ref)
		{
			ref->decrease();
		}
		if (t == nullptr) //对象为空
		{
			ref = nullptr;
		}
		else  //对象不为空
		{
			ref = new Ref<T>(t);  //新建立一个ref，里面存放该对象的地址
		}
	}
	T* get()
	{
		cout << "L_sharedPtr：获得裸指针函数" << endl;
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
		cout << "L_sharedPtr：获得引用计数函数" << endl;
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
		cout << "L_sharedPtr：判断当前是否唯一函数" << endl;
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
		cout << "L_sharedPtr：判断是否关联对象函数" << endl;
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
		cout << "shared_ptr：析构函数" << endl;
		if (ref)
		{
			ref->decrease();
		}
	}
};

template<class T> class L_weakPtr  //weak_ptr智能指针类
{
	Ref<T>* ref = nullptr;  //指向技术对象的指针
public:
	L_weakPtr() = default;  //默认构造函数
	L_weakPtr(L_sharedPtr<T>& t)
	{
		cout << "L_weakPtr：传递一个shared_ptr构造函数" << endl;
		ref = t.ref;
		if (ref)
		{
			ref->w_increase();
		}
	}
	L_weakPtr(const L_weakPtr<T>& t)
	{
		cout << "L_weakPtr：拷贝构造函数" << endl;
		ref = t.ref;
		if (ref)
		{
			ref->w_increase();
		}
	}
	L_weakPtr(L_weakPtr<T>&& t)
	{
		cout << "L_weakPtr：移动构造函数" << endl;
		ref = t.ref;
		if (ref)
		{
			t.ref = nullptr;
		}
	}
	L_weakPtr& operator=(L_weakPtr<T>& t)
	{
		cout << "L_weakPtr：拷贝=重载函数" << endl;
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
		cout << "L_weakPtr：移动=重载函数" << endl;
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
		cout << "L_weakPtr：交换ref函数" << endl;
		swap(ref, t.ref);
	}
	void reset()
	{
		cout << "L_weakPtr：释放ref函数" << endl;
		if (ref)
		{
			ref->w_decrease();
		}		
		ref = nullptr;
	}
	int use_count()
	{
		cout << "L_weakPtr：获得引用计数函数" << endl;
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
		cout << "L_weakPtr：获得一个shared_ptr" << endl;
		L_sharedPtr<T> temp(ref);
		return temp;
	}
	bool expired()
	{
		cout << "L_weakPtr：判断是否已经删除" << endl;
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
		cout << "node析构函数" << endl;
	}
};

void main()
{
	L_sharedPtr<node> node1(new node);
	L_sharedPtr<node> node2(new node);
	node1->next.operator=(node2);
	node2->pre.operator=(node1);
}


