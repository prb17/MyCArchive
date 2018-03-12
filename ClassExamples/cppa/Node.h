#ifndef NODE_H
#define NODE_H

#include<string>
using namespace std;

class Node_t
{
public:
	//	createNode()
	Node_t();
	Node_t(int value, Node_t *next);
	Node_t(const Node_t *source);
	Node_t(const Node_t &source);
	~Node_t();

	int getValue() const;
	Node_t* getNext() const;

	int setValue(int);
	Node_t* setNext(Node_t*);

	string toString() const;

private:
	int value;
	Node_t* next;
	mutable int counter;
};

ostream& operator<<(ostream& out, const Node_t* rhs);
ostream& operator<<(ostream& out, const Node_t& rhs);
//ostream& operator<<(ostream& out, const Node_t rhs);
#endif
