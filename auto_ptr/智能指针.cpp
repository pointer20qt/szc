#include <iostream>
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

template<class T> class L_autoPtr
{
public:
	T* obj = nullptr;
	L_autoPtr() = default;
	L_autoPtr(T* t)
	{
		cout << "构造函数" << endl;
		obj = t;
	}
	L_autoPtr(L_autoPtr<T>& t)
	{
		cout << "拷贝构造函数" << endl;
		obj = t.obj;
		t.obj = nullptr;//转移指针控制权
	}
	L_autoPtr& operator=(L_autoPtr<T>& t)
	{
		cout << "=重载函数函数" << endl;
		delete obj;
		obj = t.obj;
		t.obj = nullptr;//转移指针控制权
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
		cout << "释放原指针，获得新指针" << endl;
		delete obj;
		obj = t;
	}
	T* release()
	{
		cout << "释放对象控制权，返回指针" << endl;
		T* temp = obj;
		obj = nullptr;
		return temp;
	}
	~L_autoPtr()
	{
		cout << "析构函数" << endl;
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

