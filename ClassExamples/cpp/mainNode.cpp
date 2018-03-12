#include<iostream>
#include<string>
#include<vector>
#include"Node.h"
#include"List.h"

using namespace std;

void printBackwards(Node_t*);

int main(int argc, char **argv)
{
	List_t *list = new List_t();

	cout << "List output: " << list << endl;
	for(int i=0; i<10; i++)
	{
		list->insert(i);
		cout << "List: " << list << endl;
		printBackwards(list->getEnd());
	}
	for(int i=0; i<10; i++)
	{
		list->insert(i);
//		cout << "List: " << list << endl;
	}

	printBackwards(list->getEnd());

	vector<int> toRemove = {5,4,6,3,2,9,1,0,7,8};
	for(int i=0; i<10; i++)
	{
//		list->remove(toRemove[i]);
		cout << "List: " << list << endl;
		printBackwards(list->getEnd());

		List_t *newList = new List_t(list);
		cout << "Copied: " << newList << endl;
		printBackwards(newList->getEnd());
		delete newList;
	}

	List_t *newList = new List_t(list);
	cout << "NewList: " << newList << endl;
	printBackwards(newList->getEnd());

	List_t x = *newList = list;
	x = x;
	cout << "Assigned List: " << x << endl;
	cout << "List: " << list << endl;
	cout << "NewList: " << newList << endl;


	delete newList;
	delete list;
/*
	for(int i=0; i<2; i++)
	{
		cout << 4 << " apples " << i << endl;
		cerr << "error" << endl;
	}
	cout << "Enter a number: ";
	int number = 0;
	cin >> number;

	cout << "You entered: " << number << endl;

	char *buffer = (char *)malloc(20 * sizeof(char));
	cin >> buffer;
	cout << "You entered: " << buffer << endl;
	free(buffer);
	buffer = NULL;

	Node_t node;
	cout << "Printing default Node: " << node << endl;

	node.setValue(15);
	cout << "Printing Node with value 15: " << node << endl;

	//Node_t copy = new Node_t(node);
	Node_t copy(node);

	cout << "Copied node: " << copy << endl;

	Node_t *ptr = NULL;
	ptr = new Node_t();

	cout << "Pointer to default created node: " << ptr << endl;
	delete ptr;
	ptr = NULL;

	ptr = new Node_t(25, NULL, NULL);
	cout << "Pointer to explicit node (25): " << ptr << endl;

	ptr->setValue(35);
	cout << "Pointer to changed node (35): " << ptr << endl;

//	Node_t *newNode = new Node_t();
//	ptr->setNext(newNode);
	ptr->setNext(new Node_t());
	delete(ptr->getNext());
	delete ptr;
	ptr = NULL;

*/

	return 0;
}

void printBackwards(Node_t* at)
{
	while(at)
	{
		cout << at;
		at = at->getPrev();
		if(at)
		{
			cout << ", ";
		}
	}
	cout << endl;
}
