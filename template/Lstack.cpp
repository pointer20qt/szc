#include <iostream>
#include <vector>
using namespace std;


template<class T> class Lstack
{
public:
	vector<T> array;
	void push(T x)
	{
		array.push_back(x);
	}
	void pop()
	{
		array.pop_back();
	}
	T top()
	{
		return array.back();
	}
	size_t size()
	{
		return array.size();
	}
	bool empty()
	{
		return array.empty();
	}
};

void main()
{
	Lstack<int> stk;
	stk.push(2);
	stk.push(5);
	stk.pop(); 
	cout << stk.top() << endl;
	stk.push(8);
	cout << stk.size() << endl;
	stk.pop();
	cout << stk.empty() << endl;
}