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
		cout << "tool构造了" << endl;
	}
	tool(int value)
	{
		cout << "tool单参数构造了" << endl;
		this->value = value;
	}
	tool(const tool& other)
	{
		cout << "tool拷贝构造了" << endl;
		value = other.value;
	}
	tool(const tool&& other) :value(other.value)
	{
		cout << "tool移动构造了" << endl;
	}
	~tool()
	{
		cout << "tool析构了" << endl;
	}
};


template<class T> class Ref  //引用计数类
{
	int count = 0;  //指向该计数对象的智能指针数
	T* object = nullptr; //对应的对象
public:
	Ref(T* target)//构造函数
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
		if (count == 0) //如果计数为零
		{
			delete object;  //释放该计数对象对应的对象
			delete this;  //释放该计数对象
		}
	}
	int getCount()  //获取指向该计数对象的智能指针数
	{
		return count;
	}
	T* getObject()//获取指向该计数对象对应的对象
	{
		return object;
	}
};

template<class T> class L_sharedPtr  //智能指针类
{
	Ref<T>* ref = nullptr;  //指向技术对象的指针
public:
	L_sharedPtr() = default;  //默认构造函数
	L_sharedPtr(T* t)
	{
		cout << "传递指针构造函数" << endl;
		ref = new Ref<T>(t);
	}
	L_sharedPtr(const L_sharedPtr<T>& t)
	{
		cout << "拷贝构造函数" << endl;
		ref = t.ref;
		if (ref)
		{
			ref->increase();
		}
	}
	L_sharedPtr(L_sharedPtr<T>&& t)
	{
		cout << "移动构造函数" << endl;
		ref = t.ref;
		if (ref)
		{
			t.ref = nullptr;
		}
	}
	L_sharedPtr& operator=(L_sharedPtr<T>& t)
	{
		cout << "拷贝=重载函数" << endl;
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
		cout << "移动=重载函数" << endl;
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
		cout << "交换ref函数" << endl;
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
		cout << "替换对象函数" << endl;
		if (ref)
		{
			ref->decrease();
		}
		if (t == nullptr) //对象为空
		{
			ref = nullptr;
		}
		else//对象不为空
		{
			ref = new Ref<T>(t);  //新建立一个ref，里面存放该对象的地址
		}
	}
	T* get()
	{
		cout << "获得裸指针函数" << endl;
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
		cout << "获得引用计数函数" << endl;
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
		cout << "判断当前是否唯一函数" << endl;
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
		cout << "判断是否关联对象函数" << endl;
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
		cout << "智能指针析构函数" << endl;
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
	//拷贝构造ptr2，ptr.obj,ptr2.obj都指向new tool(3)
	L_sharedPtr<tool> ptr2(ptr);
	cout << (*ptr2).value << endl;
	L_sharedPtr<tool> ptr3;
	//赋值ptr3,ptr2.ptr3.obj,ptr2.obj都指向new tool(3)
	ptr3 = ptr2;
	cout << ptr->value << endl;
	cout << ptr2->value << endl;
	cout << ptr3->value << endl;
	//释放new tool(3),给ptr3.obj重新分配空间
	ptr3.reset(new tool(10));
	cout << (*ptr).value << endl;
	cout << (*ptr2).value << endl;
	cout << (*ptr3).value << endl;
	//移动构造ptr4,ptr3.obj=nullptr,
	//把ptr3原本指向的空间地址赋给ptr4
	L_sharedPtr<tool> ptr4(std::move(ptr3));
	cout << ptr4->value << endl;
}

