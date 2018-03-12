#ifndef LIST_H
#define LIST_H

#include"Node.h"
#include<string>
#include<iostream>

using namespace std;

//Doubly-Linked List
//No duplicates allowed.
class List_t
{
public:
	List_t();
	List_t(const List_t* source);
	List_t(const List_t& source);
	~List_t();

	const List_t& operator=(const List_t* rhs);
	const List_t& operator=(const List_t& rhs);

	size_t getSize() const;

	bool insert(int);
	bool remove(int);
	bool find(int) const;

	string toString() const;

	Node_t* getEnd() const;

private:
	Node_t* head;
	size_t size;
};

ostream& operator<<(ostream& out, const List_t *rhs);
ostream& operator<<(ostream& out, const List_t &rhs);



#endif
