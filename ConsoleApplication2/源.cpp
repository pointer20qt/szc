#include <iostream>
#include <iomanip>
#include <vector>
#include <queue>
#include <unordered_map>
#include <math.h>
#include <string>
#include <istream>
using namespace std;



string itos(int n){  //数字转化成字符串
	string str;
	do{
		int tmp = n % 10;
		str.insert(0, 1, (char)(tmp + 48));
		n /= 10;
	} while (n);
	return str;
}

int my_stoi(string str){
	int num = 0;
	for (int i = 0; i < str.length(); i++){
		num = num * 10 + str[i] - 48;
	}
	return num;
}

int main(int argc, char* argv[])
{
	string str = "123";
	int x = my_stoi(str);
	cout << x;
	return 0;
}