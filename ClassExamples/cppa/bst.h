#ifndef BST_H
#define BST_H

#include"bstnode.h"
#include<string>

template<typename T>
class Bst_t
{
public:
	Bst_t();
	~Bst_t();

	bool insert(T data);
	bool remove(T data);
	bool find(T data) const;

	size_t size() const;

	std::string toString() const;

private:
	Node_t<T>* head;
	size_t _size;

	bool insert(T data, Node_t<T>* at);
	void destroyNode(Node_t<T>* at);

	std::string toString(Node_t<T>* at) const;
	bool remove(T data, Node_t<T>* at, Node_t<T>* parent);
	T getNextLargest(Node_t<T>* at) const;

};

//Templated include:
#include"bst.cpp"
#endif
