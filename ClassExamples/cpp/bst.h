#ifndef BST_H
#define BST_H

#include"bstNode.h"
#include<string>

template<typename T>
class Bst_t
{
public:
	Bst_t();
	~Bst_t();

	//No duplicates allowed
	bool insert(T data);
	bool remove(T data);
	bool find(T data) const;

	size_t size() const;

	std::string toString() const;

private:
	Node_t<T>* head;
	size_t _size;

	void destroyNode(Node_t<T>* at);
	bool insert(T data, Node_t<T>* at);
	std::string toString(Node_t<T>* at) const;

	bool remove(T data, Node_t<T>* at, Node_t<T>* parent);
	T findNextLargest(Node_t<T>* at);

};


//Templated class include
#include"bst.cpp"
#endif
