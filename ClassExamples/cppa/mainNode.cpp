#include<iostream>
#include<string>
#include<vector>
#include"Node.h"
#include"List.h"

using namespace std;

int main(int argc, char **argv)
{
	List_t *list = new List_t();
	cout << "List: " << list << endl;

	for(int i=0; i<10; i++)
	{
		list->insert(i);
		cout << "List: " << list << endl;
	}
	for(int i=0; i<10; i++)
	{
		list->insert(i);
		cout << "List: " << list << endl;
	}
	vector<int> toRemove = {5,4,9,8,7,0,1,2,3,6};
	for(int i=0; i<10; i++)
	{
		list->remove(toRemove[i]);
		cout << "List: " << list << endl;

		List_t *newList = new List_t(list);
		cout << "newList: " << newList << endl;
		delete newList;
	}
//	list->insert(5);
//	cout << "List: " << list << endl;

	List_t *newList = new List_t(list);
	cout << "newList: " << newList << endl;
	newList->insert(5);
	newList->insert(8);
	newList->insert(3);
	cout << "newList: " << newList << endl;

	List_t x;
	x.insert(4);
	cout << "4List: " << x << endl;
	x = *list = newList;
	x = x;
	cout << "=xList: " << x << endl;
	cout << "=newList: " << newList << endl;
	cout << "=list: " << list << endl;

	cout << "ptrList: " << (void*)&x << endl;
	cout << "list: " << (void*)list << endl;
	cout << "newList: " << (void*)newList << endl;



	delete newList;
	delete list;
/*
	for(int i=0; i<10; i++)
	{
		cout << i << " apples." << 5 << 'a' << endl;
		cerr << "error" << endl;
	}

	cout << "Enter a number: ";
	int number;
	cin >> number;
	cout << "You entered: " << number << endl;


//	char *buffer = (char *)malloc(20 * sizeof(char));
	string buffer;
	cout << "Enter a word: ";
	cin >> buffer;
	cout << "You entered: " << buffer << endl;

	Node_t node;
	cout << "Default creation (0): " << node << endl;

	node.setValue(10);
	cout << "Modified to 10: " << node << endl;

	int y=5;
	int x(y);
	cout << x << endl;

	Node_t copy(node);
	cout << "Copy (10): " << copy << endl;

//	Node_t *ptr = new Node_t(node);
	Node_t *ptr = new Node_t(35, NULL);
	cout << "Pointer (35): " << ptr << endl;

	ptr->setValue(50);
	cout << "Pointer (50): " << ptr << endl;

	delete ptr;
	ptr = NULL;
//	free(buffer);
//	buffer = NULL;
*/
	return 0;
}
