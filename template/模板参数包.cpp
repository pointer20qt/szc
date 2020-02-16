#include <iostream>
using namespace std;

template<class T, class...args> void Lprint(T t, args...d)
{
	cout << t << endl;
	Lprint(d...);
}

void Lprint()
{
	cout << "ģ�����������" << endl;
}

void main()
{
	Lprint(1, 2.7, 3, "dhi", 'c');
}

