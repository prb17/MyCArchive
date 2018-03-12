#include<iostream>
#include<vector>
#include<string>
#include<algorithm>

using namespace std;

class Integer
{
public:
	int value;
	bool operator<(const Integer& rhs) const;
};

bool Integer::operator<(const Integer& rhs) const
{
	return value < rhs.value;
}

ostream& operator<<(ostream & out, const Integer &rhs)
{
	out << rhs.value;
	return out;
}

template<typename T>
ostream& operator<<(ostream& out, const vector<T> &rhs);

template<typename T>
void printThing(T x);

//void printThing(int x);
//void printThing(char x);

int main(int argc, char** argv)
{

//	ArrayList<Integer> x;
	vector<Integer> x;

	while(cin.good())
	{
		int num;
		cin >> num;
		Integer number;
		number.value = num;
		x.push_back(number);
		//x[x.size()] = num;
	}

	sort(x.begin(), x.end());

	cout << endl << endl;
	for(size_t i=0; i<x.size(); i++)
	{
		cout << x[i] << endl;
	}

//	size_t ten = 10;
	printThing(10);
	printThing<int>(3.45);
	printThing('c');
	string word = "apple";
	printThing(word);
	printThing(x[0]);
	printThing(x);

	return 0;
}

template<typename T>
void printThing(T x)
{
//	T something = T();
	cout << x << endl;
}


/*
void printThing(int x)
{
	cout << x << endl;
}

void printThing(char x)
{
	cout << x << endl;
}
*/


template<typename T>
ostream& operator<<(ostream& out, const vector<T> &rhs)
{
	for(size_t i=0; i<rhs.size(); i++)
	{
		out << rhs[i] << " ";
	}
	return out;
}
