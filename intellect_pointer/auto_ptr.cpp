#include<iostream>
#include<memory>
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

template<class T> class L_autoPtr  //智能指针类
{
public:
	T* obj = nullptr;
	L_autoPtr() = default;  //默认构造函数
	L_autoPtr(T* t)
	{
		cout << "构造函数" << endl;
		obj = t;
	}
	L_autoPtr(L_autoPtr<T>& t)
	{
		cout << "拷贝构造函数" << endl;
		obj = t.obj;
		t.obj = nullptr;  //转移指针控制权
	}
	L_autoPtr& operator=(L_autoPtr<T>& t)
	{
		cout << "=重载函数函数" << endl;
		delete obj;
		obj = t.obj;
		t.obj = nullptr;   //转移指针控制权
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
	L_autoPtr<tool> ptr2(ptr);   //ptr2.obj指向原本ptr.obj指向的堆空间，ptr.obj=nullptr
	L_autoPtr<tool> ptr3;
	ptr3 = ptr2;   //ptr3.obj指向原本ptr2.obj指向的堆空间，ptr2.obj=nullptr
	cout << ptr3->value << endl;
	ptr3.reset(new tool(10));  //把ptr3.obj原本指向的堆空间释放，重新在堆创建一个tool对象，ptr3.obj指向新对象
	cout << ptr3->value << endl;
	L_autoPtr<tool> ptr4(ptr3.release());  //使ptr3.obj等于空，返回ptr3.obj原本指向的堆空间的地址，并赋值给ptr4.obj
	cout << (*ptr4).value << endl;
}


