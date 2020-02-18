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


template<class T> class L_uniquePtr  //智能指针类
{
public:
	T* obj = nullptr;
	L_uniquePtr() = default;  //默认构造函数
	L_uniquePtr(T* t)
	{
		cout << "构造函数" << endl;
		obj = t;
	}
	L_uniquePtr(const L_uniquePtr<T>& t) = delete; //拷贝构造函数被删除
	L_uniquePtr(L_uniquePtr<T>&& t)
	{
		cout << "移动构造函数" << endl;
		obj = t.obj;
		t.obj = nullptr;  //转移指针控制权
	}
	L_uniquePtr& operator=(L_uniquePtr<T>& t) = delete; //拷贝=重载函数被删除
	L_uniquePtr& operator=(L_uniquePtr<T>&& t)
	{
		cout << "移动=重载函数" << endl;
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
	T* get(){
		return obj;
	}
	~L_uniquePtr()
	{
		cout << "析构函数" << endl;
		delete obj;
	}
};
void main()
{
	L_uniquePtr<tool> ptr(new tool(3));
	cout << (*ptr).value << endl;
	L_uniquePtr<tool> ptr2(std::move(ptr));  //移动构造ptr2，ptr.obj=nullptr
	cout << (*ptr2).value << endl;
	L_uniquePtr<tool> ptr3;
	ptr3 = std::move(ptr2);   //赋值ptr3,ptr2.obj=nullptr
	cout << ptr3->value << endl;
	ptr3.reset(new tool(10));  //释放new tool(3),给ptr3.obj重新分配空间
	cout << (*ptr3).value << endl;
	L_uniquePtr<tool> ptr4(std::move(ptr3.release()));  //ptr3.obj=nullptr,把ptr3原本指向的空间地址赋给ptr4
	cout << ptr4->value << endl;
}
