#ifndef NODE_H
#define NODE_H

#include<string>
#include<iostream>

using namespace std;

class Node_t
{
public:
	Node_t();
	Node_t(int, const Node_t* next, const Node_t* prev);
	Node_t(const Node_t*);
	Node_t(const Node_t&);
	~Node_t();

	int setValue(int);
	Node_t* setNext(Node_t *);
	Node_t* setPrev(Node_t *);

	int getValue() const;
	Node_t* getNext() const;
	Node_t* getPrev() const;

	string toString() const;

private:
	int value;
	Node_t *next;
	Node_t *prev;
};

ostream& operator<<(ostream& out, const Node_t *rhs);
ostream& operator<<(ostream& out, const Node_t &rhs);

#endif
