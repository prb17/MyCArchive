#include<iostream>

using namespace std;

int func(int, int);
int other(int, int);
int useFP(int, int, int(*)(int,int));

int main(int argc, char** argv)
{
//	int(*f)(int, int, int) = (int(*)(int,int,int))func;
	int(*f)(int, int) = func;
	//int(int, int) = func;
	//int *x = &y;

//	cout << f(10,12,0) << endl;
	f(10,12,0);
	f = (int(*)(int,int,int))other;

//	cout << f(10,12,0) << endl;
	f(10,12,0);

	cout << useFP(10, 12, (int(*)(int,int))f) << endl;
	cout << useFP(10, 12, func) << endl;
	cout << useFP(10, 12, other) << endl;

	return 0;
}

int useFP(int a, int b, int(*func)(int,int))
{
	return func(a,b);
}


int func(int a, int b)
{
	return a+b;
}
int other(int a, int b)
{
	return a*b;
}

