#include<iostream>
#include<vector>
#include<string>
#include<algorithm>

using namespace std;

class Integer
{
public:
//	Integer() = delete;
	int value;
	bool operator<(const Integer& rhs);
};

bool Integer::operator<(const Integer& rhs)
{
	return this->value < rhs.value;
}

ostream& operator<<(ostream& out, const Integer& rhs)
{
	out << rhs.value;
	return out;
}

template<typename T>
void dumbPrint(T x);

template<>
void dumbPrint<int>(int x);


//void dumbPrint(int x);
//void dumbPrint(char x);

int main(int argc, char** argv)
{
	int num = 5;
	int *ptr = &num;
	*ptr = 10;
	int& other = num;
	other = 10;

//	ArrayList<Integer> x = new ArrayList<Integer>();
	//vector<int> *x = new vector<int>();
	//delete x;
	vector<Integer> x;
	//vector<vector<unsigned int>> x;

	while(cin.good())
	{
		int temp;
		cin >> temp;
		if(cin.good())
		{
			Integer phony;
			phony.value = temp;
			x.push_back(phony);
		}
	}

	sort(x.begin(), x.end());

	cout << endl << endl;

	for(size_t i=0; i<x.size(); i++)
	{
		cout << x[i] << endl;
	}

	dumbPrint(10);
	dumbPrint<float>(3.45);
	dumbPrint('c');
	string word = "apple";
	dumbPrint(word);
	dumbPrint(x[0]);

	return 0;
}

template<typename T>
void swap(T* x, T* y)
{
	T temp = T();
	temp = *x;
	*x = *y;
	*y = temp;
}


template<typename T>
void dumbPrint(T x)
{
	cout << x << endl;
}


template<>
void dumbPrint<int>(int x)
{
	cout << "Quack" << endl;
}

void dumbPrint(int x)
{
	cout << x << endl;
}
void dumbPrint(char x)
{
	cout << x << endl;
}


