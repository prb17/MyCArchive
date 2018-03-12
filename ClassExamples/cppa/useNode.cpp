#include<iostream>
#include"bstnode.h"
#include"bst.h"
using namespace std;


int main(int argc, char** argv)
{
	Bst_t<int> bst;

	bst.insert(15);
	bst.insert(10);
	bst.insert(20);

	cout << bst.toString() << endl;

	bst.insert(12);
	cout << bst.toString() << endl;
	bst.insert(17);
	cout << bst.toString() << endl;
	bst.insert(22);
	cout << bst.toString() << endl;
	bst.insert(18);
	cout << bst.toString() << endl;

	bst.remove(15);
	cout << bst.toString() << endl;
	bst.remove(22);
	cout << bst.toString() << endl;
	bst.remove(10);
	cout << bst.toString() << endl;
	bst.remove(20);
	cout << bst.toString() << endl;
	bst.remove(17);
	cout << bst.toString() << endl;
	bst.remove(12);
	cout << bst.toString() << endl;
	bst.remove(18);
	cout << bst.toString() << endl;

	bst.insert(55);
	cout << bst.toString() << endl;


	return 0;
}
