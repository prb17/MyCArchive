#include<iostream>
#include<string>

using namespace std;

void passByValue(int x);
void passByPtr(int *x);
void passByReference(int &x);


int main(int argc, char** argv)
{
	int x = 1;
//	cout << x << endl;

	passByValue(x);
//	cout << x << endl;

	passByPtr(&x);
//	passByPtr(&5);
//	char *word = "bird";
//	cout << x << endl;

	passByReference(x);
	passByReference(5);
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
	*x = 5;
}

void passByReference(int& x)
{
	x = 10;
}
