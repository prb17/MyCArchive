#include<iostream>
#include<string>

using namespace std;

void passByValue(int x);
void passByPtr(int *x);
void passByReference(int &x);

//void appendString(string &x, string &y);

int main(int argc, char** argv)
{
	int x = 1;
//	cout << x << endl;

	passByValue(x);
//	cout << x << endl;

	passByPtr(&x);
//	cout << x << endl;

	passByReference(x);
//	cout << x << endl;

//	string first = "word";
//	string second = "bird";
//	appendString(first, second);
//	cout << first << endl;
//	cout << second << endl;

	return 0;
}

/*void appendString(string &x, string &y)
{
	x = x + y;
}*/


void passByValue(int x)
{
	x = 5;
}

void passByPtr(int *x)
{
//	x = 5;
	*x = 5;
}

void passByReference(int& x)
{
	x = 10;
//	&x = 5;
//	0x45454 = 5;
}
