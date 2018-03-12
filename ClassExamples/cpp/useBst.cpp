#include<iostream>
#include"bst.h"

using namespace std;

int main(int argc, char** argv)
{
//	Node_t<int> *left = new Node_t<int>(10, NULL, NULL);
//	Node_t<int> *right = new Node_t<int>(20, NULL, NULL);
//	Node_t<int> *x = new Node_t<int>(15, left, right);

//	cout << x->getData() << endl;
//	cout << x->getLeft()->getData() << endl;
//	cout << x->getRight()->getData() << endl;

//	cout << x->getLeft()->getLeft()->getData() << endl;

//	delete x;

	Bst_t<int>* myTree = new Bst_t<int>();

	myTree->insert(15);
	myTree->insert(10);
	myTree->insert(20);

	myTree->insert(12);
	myTree->insert(17);
	myTree->insert(25);
	myTree->insert(18);


	cout << myTree->toString() << endl;

	myTree->remove(15);
	cout << myTree->toString() << endl;
	myTree->remove(20);
	cout << myTree->toString() << endl;
	myTree->remove(10);
	cout << myTree->toString() << endl;

	myTree->remove(25);
	cout << myTree->toString() << endl;
	myTree->remove(12);
	cout << myTree->toString() << endl;
	myTree->remove(18);
	cout << myTree->toString() << endl;

	myTree->remove(17);
	cout << myTree->toString() << endl;

	myTree->insert(20);
	cout << myTree->toString() << endl;


	delete myTree;

	return 0;
}
